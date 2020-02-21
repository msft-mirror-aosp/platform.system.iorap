// Copyright (C) 2020 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IORAP_SRC_PACKAGE_MANAGER_REMOTE_H_
#define IORAP_SRC_PACKAGE_MANAGER_REMOTE_H_

#include <android/content/pm/IPackageManagerNative.h>
#include <binder/IServiceManager.h>

#include <optional>
#include <unordered_map>

namespace iorap::binder {

using IPackageManager = android::content::pm::IPackageManagerNative;
// A map between package name and its version.
using VersionMap = std::unordered_map<std::string, int64_t>;

class PackageManagerRemote {
 public:
  static std::shared_ptr<PackageManagerRemote> Create();

  PackageManagerRemote(android::sp<IPackageManager> package_service)
      : package_service_(package_service) {}

  // Gets the package version based on the package name.
  std::optional<int64_t> GetPackageVersion(const std::string& package_name);

  // Gets a map of package name and its version.
  VersionMap GetPackageVersionMap();

 private:
  // Gets the package manager service.
  static android::sp<IPackageManager> GetPackageService();

  // Gets all package names.
  std::vector<std::string> GetAllPackages();

  android::sp<IPackageManager> package_service_;
};
}  // namespace iorap::package_manager

#endif  // IORAP_SRC_PACKAGE_MANAGER_REMOTE_H_