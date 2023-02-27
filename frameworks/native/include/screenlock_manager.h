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

#ifndef SERVICES_INCLUDE_SCLOCK_MANAGER_H
#define SERVICES_INCLUDE_SCLOCK_MANAGER_H

#include <mutex>
#include <string>

#include "iremote_object.h"
#include "refbase.h"
#include "screenlock_manager_interface.h"
#include "screenlock_system_ability_interface.h"

namespace OHOS {
namespace ScreenLock {
class ScreenLockSaDeathRecipient : public IRemoteObject::DeathRecipient {
public:
    explicit ScreenLockSaDeathRecipient();
    ~ScreenLockSaDeathRecipient() override;
    void OnRemoteDied(const wptr<IRemoteObject> &object) override;
};

class ScreenLockManager : public RefBase {
public:
    ScreenLockManager();
    ~ScreenLockManager() override;
    static sptr<ScreenLockManager> GetInstance();
    bool IsScreenLocked();
    bool GetSecure();
    int32_t RequestUnlock(const sptr<ScreenLockSystemAbilityInterface> &listener);
    int32_t RequestLock(const sptr<ScreenLockSystemAbilityInterface> &listener);
    void OnRemoteSaDied(const wptr<IRemoteObject> &object);
    sptr<ScreenLockManagerInterface> GetProxy();

private:
    static sptr<ScreenLockManagerInterface> GetScreenLockManagerProxy();
    static std::mutex instanceLock_;
    static sptr<ScreenLockManager> instance_;
    static sptr<ScreenLockSaDeathRecipient> deathRecipient_;
    std::mutex managerProxyLock_;
    sptr<ScreenLockManagerInterface> screenlockManagerProxy_;
};
} // namespace ScreenLock
} // namespace OHOS
#endif // SERVICES_INCLUDE_SCLOCK_SERVICES_MANAGER_H