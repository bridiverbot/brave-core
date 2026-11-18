// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_BRAVE_SHIELDS_CORE_COMMON_BRAVE_SHIELD_UTILS_H_
#define BRAVE_COMPONENTS_BRAVE_SHIELDS_CORE_COMMON_BRAVE_SHIELD_UTILS_H_

#include <map>

#include "base/types/optional_ref.h"
#include "brave/components/brave_shields/core/common/shields_settings.mojom-data-view.h"
#include "components/content_settings/core/common/content_settings.h"
#include "url/origin.h"

class GURL;

namespace brave_shields {

struct ShieldsSettingCounts {
  int allow;
  int standard;
  int aggressive;
};

ContentSetting GetBraveFPContentSettingFromRules(
    const ContentSettingsForOneType& fp_rules,
    const GURL& primary_url);

ContentSetting GetBraveWebcompatContentSettingFromRules(
    const std::map<ContentSettingsType, ContentSettingsForOneType>&
        webcompat_rules,
    const GURL& primary_url,
    const ContentSettingsType content_settings_type);

ShieldsSettingCounts GetSettingCountFromRules(
    const ContentSettingsForOneType& fp_rules);

ShieldsSettingCounts GetSettingCountFromCosmeticFilteringRules(
    const ContentSettingsForOneType& fp_rules);

mojom::ContentSettingSource ConvertSettingsSource(
    const content_settings::SettingSource source);

// Returns the origin to treat as first party when applying Shields rules to a
// request. Main frames use the request URL's origin, unless it is opaque.
// Subframes, subresources and main frames with an opaque request URL origin
// use the request initiator when there is one.
url::Origin GetFirstPartyOriginForShields(
    const GURL& request_url,
    base::optional_ref<const url::Origin> request_initiator,
    bool is_main_frame);

}  // namespace brave_shields

#endif  // BRAVE_COMPONENTS_BRAVE_SHIELDS_CORE_COMMON_BRAVE_SHIELD_UTILS_H_
