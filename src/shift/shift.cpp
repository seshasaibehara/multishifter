#include "casm/casm_io/jsonParser.hh"

#include "cxxopts.hpp"
#include <iomanip>
#include <iostream>
#include <string>

#include "multishift/define.hpp"
#include "multishift/exceptions.hpp"
#include "multishift/io.hpp"
#include "multishift/misc.hpp"
#include "multishift/settings.hpp"
int _main()
{
    auto all_settings = mush::FullSettings::from_path("./mush.json");
    std::cout << all_settings.name() << std::endl;

    //***************

    const auto& base_settings = all_settings.base_settings();
    std::cout << base_settings.prim_path() << std::endl;
    std::cout << base_settings.millers().transpose() << std::endl;
    std::cout << base_settings.floor_slab_atom_index() << std::endl;
    std::cout << base_settings.stacks() << std::endl;

    auto base = mush::MultiBase::from_settings(all_settings.base_settings());

    mush::MultiIO writer(all_settings.name());
    writer.drop_base(base);

    base_settings.to_json().write(writer.base_target() / (mush::BaseSettings::tag() + ".json"));

    //***************

    const auto& shift_settings = all_settings.shift_settings();
    std::cout << shift_settings.slab_path() << std::endl;
    std::cout << shift_settings.a_points() << std::endl;
    std::cout << shift_settings.b_points() << std::endl;
    for (const auto& val : shift_settings.cleavage_values())
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    auto shifter = mush::MultiShift::from_settings(shift_settings);
    writer.drop_shifts(shifter);

    shift_settings.to_json().write(writer.shift_target() / (mush::ShiftSettings::tag() + ".json"));
    Simplicity::write_poscar(shifter.reference_slab(), writer.shift_target() / "slab.json");

    //***************

    return 0;
}

/**
 * multishift-shift takes a slab structure and some settings as input.
 * New structures are generated for both gamma surface calculations and
 * UBER calculations.
 * Gamma surface structures are created for a regular grid of shift values along
 * the slip plane (a-b vectors).
 * UBER structures are created by inserting empty space between the periodic
 * images of the slab.
 */

int main(int argc, char* argv[])
{
    using CASM::fs::path;

    cxxopts::Options options("multishift-base", "Slice the primitive cell and create a slab.");

    // clang-format off
    options.add_options()
        ("s,settings","Path to the settings file (json).",cxxopts::value<path>())
        ("h,help","Print available options.");
    // clang-format on

    try
    {
        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }

        else
        {
            cxxopts::required_argument_notify(result, std::vector<std::string>{"settings"});
        }

        const auto& settings_path = result["settings"].as<path>();

        auto all_settings = mush::FullSettings::from_path(settings_path);
        std::cout << "Using '" << all_settings.name() << "' as prefix." << std::endl;

        const auto& shift_settings = all_settings.shift_settings();
        std::cout << "Search in " << shift_settings.slab_path() << " for slab structure." << std::endl;

        std::cout << "Grid density will be ";
        std::cout << shift_settings.a_points() << "x" << shift_settings.b_points() << "("
                  << shift_settings.a_points() * shift_settings.b_points() << "grid points)." << std::endl;

        std::cout << "Cleavage values at each shift point will be:" << std::endl;
        for (auto v : shift_settings.cleavage_values())
        {
            std::cout << v << "    ";
        }
        std::cout << "    Angstrom"<<std::endl;

        loggy::divider();

        auto shifter = mush::MultiShift::from_settings(shift_settings);
        std::cout << shifter.shifted_slabs().size()<<" structures constructed." << std::endl;

        loggy::divider();

        mush::MultiIO writer(all_settings.name());
        writer.drop_shifts(shifter);

        shift_settings.to_json().write(writer.shift_target() / (mush::ShiftSettings::tag() + ".json"));
        Simplicity::write_poscar(shifter.reference_slab(), writer.shift_target() / "slab.json");

        std::cout << "Structures written to " << writer.base_target()
                  << " along with a backup of the settings and slab structure used." << std::endl;
    }

    catch (const cxxopts::missing_argument_exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Use '--help' to see option arguments" << std::endl;
        return 1;
    }

    catch (const mush::except::RequiredArgumentMissing& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Use '--help' to see options" << std::endl;
        return 2;
    }

    catch (const mush::except::UnspecifiedSettings& e)
    {
        // TODO: Be more helpful
        std::cerr << e.what() << std::endl;
        return 3;
    }

    catch (const mush::except::FileExists& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Rename it or delete it if you don't need it." << std::endl;
        return 4;
    }

    return 0;
}