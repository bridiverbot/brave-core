// Copyright (c) 2026 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/brave_shields/core/common/brave_shield_utils.h"

#include <optional>

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"
#include "url/origin.h"

namespace brave_shields {

TEST(BraveShieldUtilsTest, GetFirstPartyOriginForShieldsMainFrame) {
  const GURL url("https://example.com/page");
  const url::Origin url_origin = url::Origin::Create(url);

  EXPECT_EQ(url_origin, GetFirstPartyOriginForShields(url, std::nullopt,
                                                      /*is_main_frame=*/true));

  // The initiator is ignored, even if it is opaque.
  EXPECT_EQ(url_origin,
            GetFirstPartyOriginForShields(
                url, url::Origin::Create(GURL("https://initiator.example")),
                /*is_main_frame=*/true));
  EXPECT_EQ(url_origin, GetFirstPartyOriginForShields(url, url::Origin(),
                                                      /*is_main_frame=*/true));
}

TEST(BraveShieldUtilsTest,
     GetFirstPartyOriginForShieldsOpaqueMainFrameUsesInitiator) {
  const GURL url("data:text/html,hello");
  const url::Origin initiator =
      url::Origin::Create(GURL("https://initiator.example"));

  EXPECT_EQ(initiator, GetFirstPartyOriginForShields(url, initiator,
                                                     /*is_main_frame=*/true));

  // Without an initiator, the opaque request URL origin is used.
  EXPECT_TRUE(GetFirstPartyOriginForShields(url, std::nullopt,
                                            /*is_main_frame=*/true)
                  .opaque());
}

TEST(BraveShieldUtilsTest, GetFirstPartyOriginForShieldsNotMainFrame) {
  const GURL url("https://example.com/frame");
  const url::Origin initiator =
      url::Origin::Create(GURL("https://initiator.example"));

  // Falls back to the request URL without an initiator.
  EXPECT_EQ(url::Origin::Create(url),
            GetFirstPartyOriginForShields(url, std::nullopt,
                                          /*is_main_frame=*/false));

  EXPECT_EQ(initiator, GetFirstPartyOriginForShields(url, initiator,
                                                     /*is_main_frame=*/false));
}

}  // namespace brave_shields
