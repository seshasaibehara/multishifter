#ifndef COMMON_OPTIONS_HH
#define COMMON_OPTIONS_HH

#include <filesystem>
#include <CLI/CLI.hpp>
#include <multishift/definitions.hpp>

struct StructureIOOptions
{
    mush::fs::path input;
    mush::fs::path output;
};

void populate_subcommand_output_option(CLI::App* sub, mush::fs::path* out, bool require);
void populate_subcommand_input_option(CLI::App* sub, mush::fs::path* in, bool require);

#endif
