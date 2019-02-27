#ifndef MULTIIO_HH
#define MULTIIO_HH

#include "./define.hpp"
#include <string>
#include <tuple>

namespace CASM
{
class jsonParser;
}

namespace mush
{

class MultiBase;
class MultiShift;
class SurfacePoint;
class InterPoint;
class Interpolator;

/**
 * Given classes defined in the mush namespace, this class
 * can write out the necessary files to create gamma surfaces,
 * collect UBER data, etc.
 */

class MultiIO
{
public:
    MultiIO(const std::string& init_name);

    std::string name() const { return m_name; }

    /// Target directory for the base files
    fs::path base_target() const;

    /// Writes out preliminary structures needed before the shifts are done:
    /// primitive, shift unit, raw slab (no translation), slab
    /// Pass the associated settings along with the structures
    void drop_base(const MultiBase& preshift_structures);

    /// Target directory for the shift files
    fs::path shift_target() const;

    /// Writes out all the shifted slabs in nested directories
    void drop_shifts(const MultiShift& shifted_structures) const;

    /// Extract the fractional coordinates and values from a json file, where value is a real number
    static std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>
    unrolled_frac_grid_data_from_json(const CASM::jsonParser& json_data);

    /// Writes out all the data associated with a particular interpolator
    void drop_interpolator(const Interpolator& interpolated_data, const std::string& value_tag) const;

private:
    /// Name of the calculations directories
    std::string m_name;

    /// Directory path for a particular Surface coordinate
    fs::path _surface_point_path(const SurfacePoint& point) const;
};

} // namespace mush

#endif
