#ifndef HtmlSummary_HH
#define HtmlSummary_HH

#include "TString.h"
#include "TObject.h"
#include "TGHtml.h"
#include "TArrayF.h"
#include "TOrdCollection.h"

#include "TEveManager.h"

#include "TEveViewer.h"
#include "TGLViewer.h"

#include "TEveScene.h"

#include "TEveProjectionManager.h"
#include "TEveProjectionAxes.h"

#include "TEveBrowser.h"
#include "TEveWindow.h"

// Html table and event summary for alice_esd.C

class HtmlObjTable : public TObject
{
   public:                     // make them public for shorter code

      TString   fName;
      Int_t     fNValues;      // number of values
      Int_t     fNFields;      // number of fields
      TArrayF  *fValues;
      TString  *fLabels;
      Bool_t    fExpand;

      TString   fHtml;         // HTML output code

      void Build();
      void BuildTitle();
      void BuildLabels();
      void BuildTable();

   public:
      HtmlObjTable(const char *name, Int_t nfields, Int_t nvals, Bool_t exp=kTRUE);
      virtual ~HtmlObjTable();

      void     SetLabel(Int_t col, const char *label) { fLabels[col] = label; }
      void     SetValue(Int_t col, Int_t row, Float_t val) { fValues[col].SetAt(val, row); }
      TString  Html() const { return fHtml; }

};

//==============================================================================

class HtmlSummary
{
   public:                           // make them public for shorter code
      Int_t           fNTables;
      TOrdCollection *fObjTables;    // ->array of object tables
      TString         fHtml;         // output HTML string
      TString         fTitle;        // page title
      TString         fHeader;       // HTML header
      TString         fFooter;       // HTML footer

      void     MakeHeader();
      void     MakeFooter();

   public:
      HtmlSummary(const char *title);
      virtual ~HtmlSummary();

      HtmlObjTable  *AddTable(const char *name, Int_t nfields, Int_t nvals,
            Bool_t exp=kTRUE, Option_t *opt="");
      HtmlObjTable  *GetTable(Int_t at) const { return (HtmlObjTable *)fObjTables->At(at); }
      void           Build();
      void           Clear(Option_t *option="");
      void           Reset(Option_t *option="");
      TString        Html() const { return fHtml; }

};

#endif

