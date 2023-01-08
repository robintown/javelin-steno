//---------------------------------------------------------------------------

#pragma once
#include "../list.h"
#include "dictionary.h"

//---------------------------------------------------------------------------

struct StenoDictionaryListEntry {
  StenoDictionaryListEntry(const StenoDictionary *dictionary, bool enabled)
      : enabled(enabled), dictionary(dictionary) {}

  bool enabled;
  const StenoDictionary *dictionary;
};

//---------------------------------------------------------------------------

class StenoDictionaryList final : public StenoDictionary {
public:
  StenoDictionaryList(List<StenoDictionaryListEntry> &dictionaries);
  StenoDictionaryList(const StenoDictionary *const *dictionaries, size_t count);

  virtual StenoDictionaryLookupResult
  Lookup(const StenoDictionaryLookup &lookup) const;

  virtual const StenoDictionary *
  GetLookupProvider(const StenoDictionaryLookup &lookup) const;

  virtual void ReverseLookup(StenoReverseDictionaryLookup &result) const;
  virtual bool
  ReverseMapDictionaryLookup(StenoReverseMapDictionaryLookup &lookup) const;

  virtual size_t GetMaximumOutlineLength() const;
  virtual const char *GetName() const;
  virtual void PrintInfo(int depth) const;
  virtual bool PrintDictionary(bool hasData) const;

  virtual void ListDictionaries() const;
  virtual bool EnableDictionary(const char *name);
  virtual bool DisableDictionary(const char *name);
  virtual bool ToggleDictionary(const char *name);

  static void EnableSendDictionaryStatus() {
    isSendDictionaryStatusEnabled = true;
  }
  static void DisableSendDictionaryStatus() {
    isSendDictionaryStatusEnabled = false;
  }

  static void EnableDictionaryStatus_Binding(void *context,
                                             const char *commandLine);
  static void DisableDictionaryStatus_Binding(void *context,
                                              const char *commandLine);

private:
  List<StenoDictionaryListEntry> &dictionaries;
  size_t maximumOutlineLength;

  static bool isSendDictionaryStatusEnabled;

  void UpdateMaximumOutlineLength();

  void SendDictionaryStatus(const char *name, bool enabled) const;
};

//---------------------------------------------------------------------------
