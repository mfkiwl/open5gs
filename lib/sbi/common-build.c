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

#include "ogs-sbi.h"

OpenAPI_plmn_id_t *ogs_sbi_build_plmn_id(ogs_plmn_id_t *plmn_id)
{
    OpenAPI_plmn_id_t *PlmnId = NULL;

    ogs_assert(plmn_id);

    PlmnId = ogs_calloc(1, sizeof(*PlmnId));
    ogs_assert(PlmnId);

    PlmnId->mcc = ogs_plmn_id_mcc_string(plmn_id);
    ogs_assert(PlmnId->mcc);
    PlmnId->mnc = ogs_plmn_id_mnc_string(plmn_id);
    ogs_assert(PlmnId->mnc);

    return PlmnId;
}

ogs_plmn_id_t *ogs_sbi_parse_plmn_id(
        ogs_plmn_id_t *plmn_id, OpenAPI_plmn_id_t *PlmnId)
{
    ogs_assert(plmn_id);
    ogs_assert(PlmnId);
    ogs_assert(PlmnId->mcc);
    ogs_assert(PlmnId->mnc);

    ogs_plmn_id_build(plmn_id,
            atoi(PlmnId->mcc), atoi(PlmnId->mnc), strlen(PlmnId->mnc));
    return plmn_id;
}

void ogs_sbi_free_plmn_id(OpenAPI_plmn_id_t *PlmnId)
{
    ogs_assert(PlmnId);

    if (PlmnId->mcc)
        ogs_free(PlmnId->mcc);
    if (PlmnId->mnc)
        ogs_free(PlmnId->mnc);

    ogs_free(PlmnId);
}

OpenAPI_plmn_id_nid_t *ogs_sbi_build_plmn_id_nid(
        ogs_plmn_id_t *plmn_id, uint8_t *nid)
{
    OpenAPI_plmn_id_nid_t *PlmnIdNid = NULL;

    ogs_assert(plmn_id);

    PlmnIdNid = ogs_calloc(1, sizeof(*PlmnIdNid));
    ogs_assert(PlmnIdNid);

    PlmnIdNid->mcc = ogs_plmn_id_mcc_string(plmn_id);
    ogs_assert(PlmnIdNid->mcc);
    PlmnIdNid->mnc = ogs_plmn_id_mnc_string(plmn_id);
    ogs_assert(PlmnIdNid->mnc);

    /* TODO : Network Identifier */

    return PlmnIdNid;
}

void ogs_sbi_free_plmn_id_nid(OpenAPI_plmn_id_nid_t *PlmnIdNid)
{
    ogs_assert(PlmnIdNid);

    if (PlmnIdNid->mcc)
        ogs_free(PlmnIdNid->mcc);
    if (PlmnIdNid->mnc)
        ogs_free(PlmnIdNid->mnc);
    if (PlmnIdNid->nid)
        ogs_free(PlmnIdNid->nid);

    ogs_free(PlmnIdNid);
}

OpenAPI_guami_t *ogs_sbi_build_guami(ogs_guami_t *guami)
{
    OpenAPI_guami_t *Guami = NULL;

    ogs_assert(guami);

    Guami = ogs_calloc(1, sizeof(*Guami));
    ogs_assert(Guami);

    Guami->plmn_id = ogs_sbi_build_plmn_id(&guami->plmn_id);
    ogs_assert(Guami->plmn_id);
    Guami->amf_id = ogs_amf_id_to_string(&guami->amf_id);
    ogs_assert(Guami->amf_id);

    return Guami;
}

void ogs_sbi_free_guami(OpenAPI_guami_t *Guami)
{
    ogs_assert(Guami);

    if (Guami->plmn_id)
        ogs_sbi_free_plmn_id(Guami->plmn_id);
    if (Guami->amf_id)
        ogs_free(Guami->amf_id);
    ogs_free(Guami);
}

OpenAPI_nr_location_t *ogs_sbi_build_nr_location(
    ogs_5gs_tai_t *tai, ogs_nr_cgi_t *nr_cgi)
{
    OpenAPI_nr_location_t *NrLocation = NULL;
    OpenAPI_tai_t *Tai = NULL;
    OpenAPI_ncgi_t *Ncgi = NULL;

    ogs_assert(tai);
    ogs_assert(nr_cgi);

    Tai = ogs_calloc(1, sizeof(*Tai));
    ogs_assert(Tai);
    Tai->plmn_id = ogs_sbi_build_plmn_id(&tai->plmn_id);
    Tai->tac = ogs_uint24_to_string(tai->tac);

    Ncgi = ogs_calloc(1, sizeof(*Ncgi));
    ogs_assert(Ncgi);
    Ncgi->plmn_id = ogs_sbi_build_plmn_id(&nr_cgi->plmn_id);
    Ncgi->nr_cell_id = ogs_uint36_to_string(nr_cgi->cell_id);

    NrLocation = ogs_calloc(1, sizeof(*NrLocation));
    ogs_assert(NrLocation);
    NrLocation->tai = Tai;
    NrLocation->ncgi = Ncgi;

    return NrLocation;
}

void ogs_sbi_free_nr_location(OpenAPI_nr_location_t *NrLocation)
{
    OpenAPI_tai_t *Tai = NULL;
    OpenAPI_ncgi_t *Ncgi = NULL;

    ogs_assert(NrLocation);

    Tai = NrLocation->tai;
    if (Tai) {
        if (Tai->plmn_id)
            ogs_sbi_free_plmn_id(Tai->plmn_id);
        if (Tai->tac)
            ogs_free(Tai->tac);
        ogs_free(Tai);
    }

    Ncgi = NrLocation->ncgi;
    if (Ncgi) {
        if (Ncgi->plmn_id)
            ogs_sbi_free_plmn_id(Ncgi->plmn_id);
        if (Ncgi->nr_cell_id)
            ogs_free(Ncgi->nr_cell_id);
        ogs_free(Ncgi);
    }

    ogs_free(NrLocation);
}
