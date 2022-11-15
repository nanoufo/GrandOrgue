/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2022 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#ifndef GOORGANCONTROLLER_H
#define GOORGANCONTROLLER_H

#include <wx/hashmap.h>
#include <wx/string.h>

#include <vector>

#include "ptrvector.h"

#include "combinations/model/GOCombinationDefinition.h"
#include "control/GOEventDistributor.h"
#include "control/GOLabelControl.h"
#include "gui/GOGUIMouseState.h"
#include "model/GOModel.h"

#include "GOBitmapCache.h"
#include "GOMainWindowData.h"
#include "GOMemoryPool.h"
#include "GOPipeConfigTreeNode.h"
#include "GOTimer.h"

class GOGUIPanel;
class GOGUIPanelCreator;
class GOArchive;
class GOAudioRecorder;
class GOButtonControl;
class GOCache;
class GODivisionalSetter;
class GOElementCreator;
class GOMidi;
class GOMidiEvent;
class GOMidiPlayer;
class GOMidiRecorder;
class GOOrgan;
class GOProgressDialog;
class GOSetter;
class GOConfig;
class GOTemperament;
class GODocument;
class GOSoundEngine;
class GOSoundProvider;
class GOSoundRecorder;
class GOSoundSampler;
typedef struct _GOHashType GOHashType;

class GOOrganController : public GOEventDistributor,
                          private GOPipeUpdateCallback,
                          public GOTimer,
                          public GOModel {
  WX_DECLARE_STRING_HASH_MAP(bool, GOStringBoolMap);

private:
  GODocument *m_doc;
  wxString m_odf;
  wxString m_ArchiveID;
  wxString m_ArchivePath;
  wxString m_hash;
  wxString m_path;
  wxString m_CacheFilename;
  wxString m_SettingFilename;
  wxString m_ODFHash;
  bool m_Cacheable;
  GOSetter *m_setter;
  GODivisionalSetter *m_DivisionalSetter;
  GOAudioRecorder *m_AudioRecorder;
  GOMidiPlayer *m_MidiPlayer;
  GOMidiRecorder *m_MidiRecorder;
  int m_volume;
  bool m_IgnorePitch;
  wxString m_Temperament;
  unsigned m_releaseTail = 0;

  bool m_b_customized;
  bool m_DivisionalsStoreIntermanualCouplers;
  bool m_DivisionalsStoreIntramanualCouplers;
  bool m_DivisionalsStoreTremulants;
  bool m_GeneralsStoreDivisionalCouplers;
  bool m_CombinationsStoreNonDisplayedDrawstops;

  wxString m_ChurchName;
  wxString m_ChurchAddress;
  wxString m_OrganBuilder;
  wxString m_OrganBuildDate;
  wxString m_OrganComments;
  wxString m_RecordingDetails;
  wxString m_InfoFilename;

  ptr_vector<GOGUIPanel> m_panels;
  ptr_vector<GOGUIPanelCreator> m_panelcreators;
  ptr_vector<GOElementCreator> m_elementcreators;
  ptr_vector<GOArchive> m_archives;
  GOStringBoolMap m_UsedSections;

  GOSoundEngine *m_soundengine;
  GOMidi *m_midi;
  std::vector<bool> m_MidiSamplesetMatch;
  int m_SampleSetId1, m_SampleSetId2;
  GOGUIMouseState m_MouseState;

  GOMemoryPool m_pool;
  GOBitmapCache m_bitmaps;
  GOPipeConfigTreeNode m_PipeConfig;
  GOConfig &m_config;
  GOCombinationDefinition m_GeneralTemplate;
  GOLabelControl m_PitchLabel;
  GOLabelControl m_TemperamentLabel;
  GOMainWindowData m_MainWindowData;

  void ReadOrganFile(GOConfigReader &cfg);
  GOHashType GenerateCacheHash();
  wxString GenerateSettingFileName();
  wxString GenerateCacheFileName();
  void SetTemperament(const GOTemperament &temperament);
  void PreconfigRecorder();

  void UpdateAmplitude();
  void UpdateTuning();
  void UpdateAudioGroup();

  wxString GetOrganHash();

  bool LoadArchive(
    wxString ID, wxString &name, const wxString &parentID = wxEmptyString);
  void CloseArchives();

public:
  GOOrganController(GODocument *doc, GOConfig &settings);
  wxString Load(
    GOProgressDialog *dlg,
    const GOOrgan &organ,
    const wxString &cmb = wxEmptyString);
  void LoadCombination(const wxString &cmb);
  bool Save();
  bool Export(const wxString &cmb);
  bool CachePresent();
  bool IsCacheable();
  bool UpdateCache(GOProgressDialog *dlg, bool compress);
  void DeleteCache();
  void DeleteSettings();
  ;
  void Abort();
  void PreparePlayback(
    GOSoundEngine *engine, GOMidi *midi, GOSoundRecorder *recorder);
  void PrepareRecording();
  void Update();
  void Reset();
  void ProcessMidi(const GOMidiEvent &event);
  void AllNotesOff();
  void Modified();
  GODocument *GetDocument();
  ~GOOrganController(void);

  /* Access to internal ODF objects */
  GOSetter *GetSetter();
  GOGUIPanel *GetPanel(unsigned index);
  unsigned GetPanelCount();
  void AddPanel(GOGUIPanel *panel);
  GOMemoryPool &GetMemoryPool();
  GOConfig &GetSettings();
  GOBitmapCache &GetBitmapCache();
  GOPipeConfigNode &GetPipeConfig();
  void SetTemperament(wxString name);
  wxString GetTemperament();
  void MarkSectionInUse(wxString name);

  bool useArchives();
  GOArchive *findArchive(const wxString &name);

  int GetRecorderElementID(wxString name);
  GOCombinationDefinition &GetGeneralTemplate();
  GOLabelControl *GetPitchLabel();
  GOLabelControl *GetTemperamentLabel();
  GOMainWindowData *GetMainWindowData();

  void LoadMIDIFile(const wxString &filename);

  /* ODF general properties */
  bool DivisionalsStoreIntermanualCouplers();
  bool DivisionalsStoreIntramanualCouplers();
  bool DivisionalsStoreTremulants();
  bool CombinationsStoreNonDisplayedDrawstops();
  bool GeneralsStoreDivisionalCouplers();

  void SetVolume(int volume);
  int GetVolume();

  void SetIgnorePitch(bool ignorepitch);
  bool GetIgnorePitch();

  unsigned GetReleaseTail() const { return m_releaseTail; }
  void SetReleaseTail(unsigned releaseTail);

  GOEnclosure *GetEnclosure(const wxString &name, bool is_panel = false);
  GOLabelControl *GetLabel(const wxString &name, bool is_panel = false);
  GOButtonControl *GetButtonControl(
    const wxString &name, bool is_panel = false);

  /* TODO: can somebody figure out what this thing is */
  bool IsCustomized();

  /* Filename of the organ definition used to load */
  const wxString GetODFFilename();
  const wxString GetODFPath();
  const wxString GetOrganPathInfo();
  GOOrgan GetOrganInfo();
  const wxString GetSettingFilename();
  const wxString GetCacheFilename();

  /* Organ and Building general information */
  const wxString &GetChurchName();
  const wxString &GetChurchAddress();
  const wxString &GetOrganBuilder();
  const wxString &GetOrganBuildDate();
  const wxString &GetOrganComments();
  const wxString &GetRecordingDetails();
  const wxString &GetInfoFilename();

  GOSoundSampler *StartSample(
    const GOSoundProvider *pipe,
    int sampler_group_id,
    unsigned audio_group,
    unsigned velocity,
    unsigned delay,
    uint64_t last_stop);
  uint64_t StopSample(const GOSoundProvider *pipe, GOSoundSampler *handle);
  void SwitchSample(const GOSoundProvider *pipe, GOSoundSampler *handle);
  void UpdateVelocity(
    const GOSoundProvider *pipe, GOSoundSampler *handle, unsigned velocity);

  void SendMidiMessage(GOMidiEvent &e);
  void SendMidiRecorderMessage(GOMidiEvent &e);
  GOMidi *GetMidi();

  GOGUIMouseState &GetMouseState() { return m_MouseState; }

  /* For testing only */
  void SetODFPath(wxString path);
};

#endif