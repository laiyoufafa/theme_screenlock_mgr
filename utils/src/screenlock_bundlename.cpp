/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "screenlock_bundlename.h"

#include "bundle_manager_helper.h"

namespace OHOS {
namespace ScreenLock {
ScreenLockBundleName::ScreenLockBundleName()
{
}

bool ScreenLockBundleName::GetBundleNameByUid(std::int32_t uid, std::string &bname)
{
    std::shared_ptr<EventFwk::BundleManagerHelper> bundleManager = EventFwk::BundleManagerHelper::GetInstance();
    if (bundleManager != nullptr) {
        bname = bundleManager->GetBundleName(uid);
    }
    return true;
}
} // namespace ScreenLock
} // namespace OHOS
