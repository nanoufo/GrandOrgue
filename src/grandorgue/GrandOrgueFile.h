/*
 * GrandOrgue - free pipe organ simulator
 *
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2012 GrandOrgue contributors (see AUTHORS)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef GRANDORGUEFILE_H
#define GRANDORGUEFILE_H

#include <vector>
#include "ptrvector.h"
#include <wx/wx.h>
#include "GOrgueBitmapCache.h"
#include "GOrgueCombinationDefinition.h"
#include "GOrgueLabel.h"
#include "GOrgueMemoryPool.h"
#include "GOrguePipeConfig.h"

class wxProgressDialog;

class GOrgueCache;
class GOrgueCacheObject;
class GOrgueDivisionalCoupler;
class GOrgueEnclosure;
class GOrgueGeneral;
class GOrgueManual;
class GOrgueMidi;
class GOrgueMidiEvent;
class GOrguePiston;
class GOrguePushbutton;
class GOrgueRank;
class GOrgueSetter;
class GOrgueSettings;
class GOrgueTemperament;
class GOrgueTremulant;
class GOrgueWindchest;
class GOGUIPanel;
class OrganDocument;
class GOSoundProvider;
class GOSoundEngine;
typedef struct GO_SAMPLER_T* SAMPLER_HANDLE;

class GrandOrgueFile : public GOrguePipeUpdateCallback
{

private:

	OrganDocument* m_doc;
	wxString m_odf;
	wxString m_path;
	wxString m_CacheFilename;
	wxString m_SettingFilename;
	GOrgueSetter* m_setter;
	int m_volume;
	bool m_IgnorePitch;
	wxString m_Temperament;

	bool m_b_customized;
	bool m_DivisionalsStoreIntermanualCouplers;
	bool m_DivisionalsStoreIntramanualCouplers;
	bool m_DivisionalsStoreTremulants;
	bool m_GeneralsStoreDivisionalCouplers;
	bool m_CombinationsStoreNonDisplayedDrawstops;

	wxInt16 m_HighestSampleFormat;
	wxInt16 m_FirstManual;

	float m_AmplitudeLevel;
	float m_Amplitude;
	float m_DefaultTuning;
	float m_Tuning;

	wxString m_HauptwerkOrganFileFormatVersion;
	wxString m_ChurchName;
	wxString m_ChurchAddress;
	wxString m_OrganBuilder;
	wxString m_OrganBuildDate;
	wxString m_OrganComments;
	wxString m_RecordingDetails;
	wxString m_InfoFilename;
	unsigned m_RankCount;
	unsigned m_ODFManualCount;

	ptr_vector<GOrgueEnclosure> m_enclosure;
	ptr_vector<GOrgueTremulant> m_tremulant;
	ptr_vector<GOrgueWindchest> m_windchest;
	ptr_vector<GOrguePiston> m_piston;
	ptr_vector<GOrgueGeneral> m_general;
	ptr_vector<GOrgueDivisionalCoupler> m_divisionalcoupler;
	ptr_vector<GOrgueRank> m_ranks;
	ptr_vector<GOrgueManual> m_manual;
	ptr_vector<GOGUIPanel> m_panels;

	GOSoundEngine* m_soundengine;
	GOrgueMidi* m_midi;

	GOrgueMemoryPool m_pool;
	GOrgueBitmapCache m_bitmaps;
	GOrguePipeConfig m_PipeConfig;
	GOrgueSettings& m_Settings;
	GOrgueCombinationDefinition m_GeneralTemplate;
	GOrgueLabel m_PitchLabel;
	GOrgueLabel m_TemperamentLabel;

	void ReadOrganFile(GOrgueConfigReader& cfg);
	void ReadCombinations(GOrgueConfigReader& cfg);
	bool TryLoad(GOrgueCache* cache, wxProgressDialog& dlg, wxString& error);
	void GenerateCacheHash(unsigned char hash[20]);
	wxString GenerateSettingFileName();
	wxString GenerateCacheFileName();
	void SetTemperament(const GOrgueTemperament& temperament);
	void GenerateCacheObjectList(std::vector<GOrgueCacheObject*>& objects);
	void ResolveReferences();

public:

	GrandOrgueFile(OrganDocument* doc, GOrgueSettings& settings);
	wxString Load(const wxString& file, const wxString& file2 = wxEmptyString);
	void LoadCombination(const wxString& file);
	void Save(const wxString& file);
	bool CachePresent();
	bool UpdateCache(bool compress);
	void DeleteCache();
	void DeleteSettings();;
	void Abort();
	void PreparePlayback(GOSoundEngine* engine, GOrgueMidi* midi);
	void Reset();
	void ProcessMidi(const GOrgueMidiEvent& event);
	void HandleKey(int key);
	void ControlChanged(void* control);
	void Modified();
	~GrandOrgueFile(void);

	/* Access to internal ODF objects */
	unsigned GetManualAndPedalCount();
	unsigned GetODFManualCount();
	unsigned GetFirstManualIndex();
	GOrgueManual* GetManual(unsigned index);
	unsigned GetTremulantCount();
	GOrgueRank* GetRank(unsigned index);
	unsigned GetRankCount();
	void AddRank(GOrgueRank* rank);
	GOrgueTremulant* GetTremulant(unsigned index);
	unsigned GetDivisionalCouplerCount();
	GOrgueDivisionalCoupler* GetDivisionalCoupler(unsigned index);
	unsigned GetGeneralCount();
	GOrgueGeneral* GetGeneral(unsigned index);
	unsigned GetNumberOfReversiblePistons();
	GOrguePiston* GetPiston(unsigned index);
	GOrgueSetter* GetSetter();
	unsigned AddWindchest(GOrgueWindchest* windchest);
	GOrgueWindchest* GetWindchest(unsigned index);
	unsigned GetWindchestGroupCount();
	GOrgueEnclosure* GetEnclosure(unsigned index);
	unsigned GetEnclosureCount();
	unsigned AddEnclosure(GOrgueEnclosure* enclosure);
	GOGUIPanel* GetPanel(unsigned index);
	unsigned GetPanelCount();
	GOrgueMemoryPool& GetMemoryPool();
	GOrgueSettings& GetSettings();
	GOrgueBitmapCache& GetBitmapCache();
	GOrguePipeConfig& GetPipeConfig();
	void SetTemperament(wxString name);
	wxString GetTemperament();

	GOrgueCombinationDefinition& GetGeneralTemplate();
	GOrgueLabel* GetPitchLabel();
	GOrgueLabel* GetTemperamentLabel();

	/* ODF general properties */
	bool DivisionalsStoreIntermanualCouplers();
	bool DivisionalsStoreIntramanualCouplers();
	bool DivisionalsStoreTremulants();
	bool CombinationsStoreNonDisplayedDrawstops();
	bool GeneralsStoreDivisionalCouplers();

	void SetVolume(int volume);
	int GetVolume();

	void UpdateAmplitude();
	void UpdateTuning();
	void UpdateAudioGroup();
	
	void SetIgnorePitch(bool ignorepitch);
	bool GetIgnorePitch();
	
	/* TODO: can somebody figure out what this thing is */
	bool IsCustomized();

	/* Filename of the organ definition used to load */
	const wxString GetODFFilename();
	const wxString GetODFPath();
	const wxString GetSettingFilename();
	const wxString GetCacheFilename();

	/* Organ and Building general information */
	const wxString& GetChurchName();
	const wxString& GetChurchAddress();
	const wxString& GetOrganBuilder();
	const wxString& GetOrganBuildDate();
	const wxString& GetOrganComments();
	const wxString& GetRecordingDetails();
	const wxString& GetInfoFilename();

	SAMPLER_HANDLE StartSample(const GOSoundProvider *pipe, int sampler_group_id, unsigned audio_group);
	void StopSample(const GOSoundProvider *pipe, SAMPLER_HANDLE handle);
	void SwitchSample(const GOSoundProvider *pipe, SAMPLER_HANDLE handle);

	void SendMidiMessage(GOrgueMidiEvent& e);
	void SetMidiListener(wxEvtHandler* event_handler);
};

#endif
