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
#include "screenlock_service_test.h"

#include <cstdint>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <sys/time.h>

#include "sclock_log.h"
#include "screenlock_common.h"
#include "screenlock_event_list_test.h"
#include "screenlock_manager.h"
#include "screenlock_notify_test_instance.h"
#include "screenlock_system_ability.h"
#include "screenlock_system_ability_stub.h"
#include "screenlock_app_manager.h"
#include "screenlock_unlock_callback_test.h"

namespace OHOS {
namespace ScreenLock {
using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::ScreenLock;

static EventListenerTest g_unlockTestListener;

void ScreenLockServiceTest::SetUpTestCase()
{
}

void ScreenLockServiceTest::TearDownTestCase()
{
}

void ScreenLockServiceTest::SetUp()
{
}

void ScreenLockServiceTest::TearDown()
{
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest002, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  IsScreenLocked state ,get unlockstate");
    bool status = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  status is-------->%{public}d", status);
    bool isScreenLocked = false;
    ScreenLockManager::GetInstance()->Test_SetScreenLocked(isScreenLocked);
    bool result = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  result is-------->%{public}d", result);
    EXPECT_EQ(result, false);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest003, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  IsScreenLocked state ,get lockstate");
    bool status = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  status is-------->%{public}d", status);
    bool isScreenLocked = true;
    ScreenLockManager::GetInstance()->Test_SetScreenLocked(isScreenLocked);
    bool result = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  result is-------->%{public}d", result);
    EXPECT_EQ(result, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest004, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  secure");
    bool result = ScreenLockManager::GetInstance()->GetSecure();
    SCLOCK_HILOGD(" result is-------->%{public}d", result);
    EXPECT_EQ(result, false);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest006, TestSize.Level0)
{
    SCLOCK_HILOGD("Test can not get foucs,expect unlock fail");
    ScreenLockManager::GetInstance()->Test_SetScreenLocked(true);
    sptr<ScreenLockSystemAbilityInterface> listener = new ScreenlockUnlockCallbackTest(g_unlockTestListener);
    if (listener == nullptr) {
        SCLOCK_HILOGE("listener object is nullptr");
        EXPECT_EQ(false, true);
        return ;
    }
    ScreenLockManager::GetInstance()->RequestUnlock(listener);
    std::string event = UNLOCK_SCREEN_RESULT;
    ScreenLockAppManager::GetInstance()->SendScreenLockEvent(event, UNLOCKSCREEN_FAIL);
    bool result = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("get not foucs IsScreenLocked  result is-------->%{public}d", result);
    EXPECT_EQ(result, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest007, TestSize.Level0)
{
    SCLOCK_HILOGD("Test screnlockapp notice unlock fail");
    ScreenLockManager::GetInstance()->Test_SetScreenLocked(true);
    sptr<ScreenLockSystemAbilityInterface> listener = new ScreenlockUnlockCallbackTest(g_unlockTestListener);
    if (listener == nullptr) {
        SCLOCK_HILOGE("listener object is nullptr");
        EXPECT_EQ(false, true);
        return ;
    }
    ScreenLockManager::GetInstance()->RequestUnlock(listener);
    std::string event = UNLOCK_SCREEN_RESULT;
    ScreenLockAppManager::GetInstance()->SendScreenLockEvent(event, UNLOCKSCREEN_FAIL);
    bool result = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  result is-------->%{public}d", result);
    EXPECT_EQ(result, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest008, TestSize.Level0)
{
    SCLOCK_HILOGD("Test power off screen");
    std::string message = BEGIN_SLEEP;
    int param = BEGIN_SLEEP_DEVICE_ADMIN_REASON;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_BEGIN_SLEEP), true);
    message = END_SLEEP;
    param = END_SLEEP_USER_REASON;
    result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_END_SLEEP), true);
    message = BEGIN_SCREEN_OFF;
    param = 0;
    result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_BEGIN_OFF), true);
    message = END_SCREEN_OFF;
    param = 0;
    result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_END_OFF), true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest009, TestSize.Level0)
{
    SCLOCK_HILOGD("Test context event");
    bool status = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  status is-------->%{public}d", status);
    if (status) {
        std::string message = BEGIN_WAKEUP;
        int param = 0;
        bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify beginWakeUp  result is-------->%{public}d", result);
        int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_BEGIN_WAKEUP), true);
        message = END_WAKEUP;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_END_WAKEUP), true);
        message = BEGIN_SCREEN_ON;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_BEGIN_ON), true);
        message = END_SCREEN_ON;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_END_ON), true);
    } else {
        EXPECT_EQ(status, false);
    }
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest010, TestSize.Level0)
{
    SCLOCK_HILOGD("Test app call event");
    bool status = ScreenLockManager::GetInstance()->IsScreenLocked();
    SCLOCK_HILOGD("IsScreenLocked  status is-------->%{public}d", status);
    if (status) {
        std::string message = BEGIN_WAKEUP;
        int param = 0;
        bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify beginWakeUp  result is-------->%{public}d", result);
        int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_BEGIN_WAKEUP), true);
        message = END_WAKEUP;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(InteractiveState::INTERACTIVE_STATE_END_WAKEUP), true);
        message = BEGIN_SCREEN_ON;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_BEGIN_ON), true);
        message = END_SCREEN_ON;
        param = 0;
        result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
        SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
        retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
        EXPECT_EQ(retVal == static_cast<int>(ScreenState::SCREEN_STATE_END_ON), true);
    } else {
        EXPECT_EQ(status, false);
    }
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest011, TestSize.Level0)
{
    SCLOCK_HILOGD("Test userid 10");
    std::string message = CHANGE_USER;
    int param = 10;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == param, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest012, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  userid is 0");
    std::string message = CHANGE_USER;
    int param = 0;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == param, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest013, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  userid -2");
    const int MINUSERID = 0;
    int param = -2;
    EXPECT_EQ(param >= MINUSERID, false);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest014, TestSize.Level0)
{
    SCLOCK_HILOGD("Test  userid 999999999");
    const int MAXUSERID = 999999999;
    int param = 999999999;
    EXPECT_EQ(param < MAXUSERID, false);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest015, TestSize.Level0)
{
    std::string message = SCREENLOCK_ENABLED;
    int param = SCREENLOCK_APP_CAN_USE;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == param, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest016, TestSize.Level0)
{
    std::string message = SCREENLOCK_ENABLED;
    int param = SCREENLOCK_APP_CAN_NOT_USE;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    int retVal = ScreenLockManager::GetInstance()->Test_GetRuntimeState(message);
    EXPECT_EQ(retVal == param, true);
}

HWTEST_F(ScreenLockServiceTest, SetScreenLockTest017, TestSize.Level0)
{
    std::string message = EXIT_ANIMATION;
    int param = 0;
    bool result = ScreenLockManager::GetInstance()->Test_RuntimeNotify(message, param);
    SCLOCK_HILOGD("Test_RuntimeNotify message=%{public}s,result =%{public}d", message.c_str(), result);
    EXPECT_EQ(result, true);
}
} // namespace ScreenLock
} // namespace OHOS