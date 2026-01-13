#include "filesystem.h"

#include <filesystem>

std::string basePath(){
    auto p = std::filesystem::current_path();

    while (!p.empty() && p.filename() != "Veylorn") {
        p = p.parent_path();
    }

    return p.string() + "/";
}
