/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OGS_COMMON_BUILD_H
#define OGS_COMMON_BUILD_H

#ifdef __cplusplus
extern "C" {
#endif

OpenAPI_plmn_id_t *ogs_sbi_build_plmn_id(ogs_plmn_id_t *plmn_id);
ogs_plmn_id_t *ogs_sbi_parse_plmn_id(
        ogs_plmn_id_t *plmn_id, OpenAPI_plmn_id_t *PlmnId);
void ogs_sbi_free_plmn_id(OpenAPI_plmn_id_t *PlmnId);

OpenAPI_plmn_id_nid_t *ogs_sbi_build_plmn_id_nid(
        ogs_plmn_id_t *plmn_id, uint8_t *nid);
void ogs_sbi_free_plmn_id_nid(OpenAPI_plmn_id_nid_t *PlmnIdNid);

OpenAPI_guami_t *ogs_sbi_build_guami(ogs_guami_t *guami);
void ogs_sbi_free_guami(OpenAPI_guami_t *Guami);

OpenAPI_nr_location_t *ogs_sbi_build_nr_location(
    ogs_5gs_tai_t *tai, ogs_nr_cgi_t *nr_cgi);
void ogs_sbi_free_nr_location(OpenAPI_nr_location_t *NrLocation);

#ifdef __cplusplus
}
#endif

#endif /* OGS_COMMON_BUILD_H */
