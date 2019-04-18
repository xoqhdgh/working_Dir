void draw_hist() {

/*Histogram Parameters*/
double XMIN = -1;
double XMAX = -1;
long YMAX = 60000;
int rebin = 5;

/*Physics Parameters*/
double Lumi = 3000000.0;

long double xsecSignal1=6.02158250669e-04;//2TeV
long double xsecSignal2=1.89757563679e-06;//5TeV
long double xsecw2j100to500=22.4645492;
long double xsecw2j500to1000=0.220401086;
long double xsecw2j1000to2000=0.00847007776;
long double xsecw2j2000to3000=6.160953643e-05;
long double xsecw2j3000to4000=6.5935273893e-07;
long double xsecw2j4000to5000=5.62906155243e-09;
long double xsecw2j5000to6000=2.39018329425e-11;
long double xsecw2j6000toinf=7.29251198043e-15;

int NSignal1      =1000000;
int NSignal2      =1000000;
int Nw2j100to500  =1000000;
int Nw2j500to1000 =1000000;
int Nw2j1000to2000=1000000;
int Nw2j2000to3000=1000000;
int Nw2j3000to4000=1000000;
int Nw2j4000to5000=1000000;
int Nw2j5000to6000=1000000;
int Nw2j6000toinf =1000000;

TString dataname = "_VBFcut";//Choose data and Write plot title

/*Read Draft Rootfile*/
TFile* fSignal1       = TFile::Open("Signal/signal_2000mass"+dataname+".root");
TFile* fSignal2       = TFile::Open("Signal/signal_5000mass"+dataname+".root");
TFile* fw2j100to500   = TFile::Open("W2jet/wjets_500Mjj_4mom100to500"+dataname+".root");
TFile* fw2j500to1000  = TFile::Open("W2jet/wjets_500Mjj_4mom500to1000"+dataname+".root");
TFile* fw2j1000to2000 = TFile::Open("W2jet/wjets_500Mjj_4mom1000to2000"+dataname+".root");
TFile* fw2j2000to3000 = TFile::Open("W2jet/wjets_500Mjj_4mom2000to3000"+dataname+".root");
TFile* fw2j3000to4000 = TFile::Open("W2jet/wjets_500Mjj_4mom3000to4000"+dataname+".root");
TFile* fw2j4000to5000 = TFile::Open("W2jet/wjets_500Mjj_4mom4000to5000"+dataname+".root");
TFile* fw2j5000to6000 = TFile::Open("W2jet/wjets_500Mjj_4mom5000to6000"+dataname+".root");
TFile* fw2j6000toinf  = TFile::Open("W2jet/wjets_500Mjj_4mom6000toinf"+dataname+".root");

/*Histogram list in Rootfile*/
//TString histname = "PT_ele";       rebin=300; XMIN=0;  XMAX=2000;        YMAX=100000000;   TString title_name="PT_{e}";                char unit[]="GeV";
//TString histname = "PT_nue";       rebin=300; XMIN=0;  XMAX=2000;        YMAX=100000000;   TString title_name="PT_{v}";                char unit[]="GeV";
//TString histname = "Mt_ev";        rebin=100; XMIN=0;  XMAX=7000;        YMAX=100000;      TString title_name="M_{T}(GeV)";            char unit[]="GeV";
//TString histname = "ratio_ev";     rebin=100; XMIN=0;  XMAX=40;          YMAX=1000000;     TString title_name="E^{e}_{T}/E^{#nu}_{T}"; char unit[]="";
//TString histname = "delta_Phi_ev"; rebin=200; XMIN=0;  XMAX=TMath::Pi(); YMAX=100000000;   TString title_name="#Delta#phi_{ev}(rad)";  char unit[]="rad";

//TString histname = "jets_PT";      rebin=250; XMIN=0;  XMAX=7000;        YMAX=100000000;   TString title_name="PT_{j}";                char unit[]="GeV";
//TString histname = "jets_eta";     rebin=250; XMIN=-5; XMAX=5;           YMAX=100000000;   TString title_name="#eta_{j}";              char unit[]="";
//TString histname = "delta_Eta_jj"; rebin=200; XMIN=0;  XMAX=10;          YMAX=100000000;   TString title_name="Dijet #Delta#eta";      char unit[]="";
//TString histname = "delta_Phi_jj"; rebin=200; XMIN=0;  XMAX=TMath::Pi(); YMAX=100000000;   TString title_name="#Delta#Phi_{jj}";       char unit[]="rad";
//TString histname = "Mjj";          rebin=200; XMIN=0;  XMAX=10000;       YMAX=10000000000; TString title_name="Dijet mass(GeV)";       char unit[]="GeV";
//TString histname = "Zeppenfeld";   rebin=200; XMIN=0;  XMAX=10;          YMAX=100000000;   TString title_name="Z";                     char unit[]="";
TString histname = "Centrality";   rebin=200; XMIN=0;  XMAX=10;          YMAX=100000000;   TString title_name="Centrality";            char unit[]="";  

//TString histname = "delta_R_jj";   rebin=200; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="#Delta R_{jj}";         char unit[]="";
//TString histname = "ratio_jj";     rebin=400; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="ratio_{jj}";            char unit[]="";
//TString histname = "delta_R_ej1";  rebin=200; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="#Delta R_{ej1}";        char unit[]="";
//TString histname = "delta_R_ej2";  rebin=200; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="#Delta R_{ej2}";        char unit[]="";
//TString histname = "delta_R_wj1";  rebin=200; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="#Delta R_{wj1}";        char unit[]="";
//TString histname = "delta_R_wj2";  rebin=200; XMIN=0;  XMAX=20;          YMAX=100000000;   TString title_name="#Delta R_{wj2}";        char unit[]="";

/*Get Histogram & Normalizing*/
TH1F* hSignal1       = (TH1F*)fSignal1      ->Get(histname); hSignal1      ->Scale(xsecSignal1/NSignal1*Lumi);
TH1F* hSignal2       = (TH1F*)fSignal2      ->Get(histname); hSignal2      ->Scale(xsecSignal2/NSignal2*Lumi);
TH1F* hw2j100to500   = (TH1F*)fw2j100to500  ->Get(histname); hw2j100to500  ->Scale(xsecw2j100to500/Nw2j100to500*Lumi);
TH1F* hw2j500to1000  = (TH1F*)fw2j500to1000 ->Get(histname); hw2j500to1000 ->Scale(xsecw2j500to1000/Nw2j500to1000*Lumi);
TH1F* hw2j1000to2000 = (TH1F*)fw2j1000to2000->Get(histname); hw2j1000to2000->Scale(xsecw2j1000to2000/Nw2j1000to2000*Lumi);
TH1F* hw2j2000to3000 = (TH1F*)fw2j2000to3000->Get(histname); hw2j2000to3000->Scale(xsecw2j2000to3000/Nw2j2000to3000*Lumi);
TH1F* hw2j3000to4000 = (TH1F*)fw2j3000to4000->Get(histname); hw2j3000to4000->Scale(xsecw2j3000to4000/Nw2j3000to4000*Lumi);
TH1F* hw2j4000to5000 = (TH1F*)fw2j4000to5000->Get(histname); hw2j4000to5000->Scale(xsecw2j4000to5000/Nw2j4000to5000*Lumi);
TH1F* hw2j5000to6000 = (TH1F*)fw2j5000to6000->Get(histname); hw2j5000to6000->Scale(xsecw2j5000to6000/Nw2j5000to6000*Lumi);
TH1F* hw2j6000toinf  = (TH1F*)fw2j6000toinf ->Get(histname); hw2j6000toinf ->Scale(xsecw2j6000toinf/Nw2j6000toinf*Lumi);

/*Design Histogram*/
hSignal1->SetLineWidth(3);       hSignal1       ->SetLineColor(kOrange+8); hSignal1      ->Rebin(rebin);
hSignal2->SetLineWidth(3);       hSignal2       ->SetLineColor(kViolet+8); hSignal2      ->Rebin(rebin);
hw2j100to500  ->SetFillColor(kTeal-5); hw2j100to500   ->SetLineColor(kTeal-5); hw2j100to500  ->Rebin(rebin);
hw2j500to1000 ->SetFillColor(kTeal-5); hw2j500to1000  ->SetLineColor(kTeal-5); hw2j500to1000 ->Rebin(rebin);
hw2j1000to2000->SetFillColor(kTeal-5); hw2j1000to2000 ->SetLineColor(kTeal-5); hw2j1000to2000->Rebin(rebin);
hw2j2000to3000->SetFillColor(kTeal-5); hw2j2000to3000 ->SetLineColor(kTeal-5); hw2j2000to3000->Rebin(rebin);
hw2j3000to4000->SetFillColor(kTeal-5); hw2j3000to4000 ->SetLineColor(kTeal-5); hw2j3000to4000->Rebin(rebin);
hw2j4000to5000->SetFillColor(kTeal-5); hw2j4000to5000 ->SetLineColor(kTeal-5); hw2j4000to5000->Rebin(rebin);
hw2j5000to6000->SetFillColor(kTeal-5); hw2j5000to6000 ->SetLineColor(kTeal-5); hw2j5000to6000->Rebin(rebin);
hw2j6000toinf ->SetFillColor(kTeal-5); hw2j6000toinf  ->SetLineColor(kTeal-5); hw2j6000toinf ->Rebin(rebin);

double binwidth= hSignal1->GetBinWidth(1);

/*Stack Background*/
THStack* stkBkgs = new THStack("stkBkgs","stkBkgs");

stkBkgs->Add(hw2j6000toinf);
stkBkgs->Add(hw2j5000to6000);
stkBkgs->Add(hw2j4000to5000);
stkBkgs->Add(hw2j3000to4000);
stkBkgs->Add(hw2j2000to3000);
stkBkgs->Add(hw2j1000to2000);
stkBkgs->Add(hw2j500to1000);
stkBkgs->Add(hw2j100to500);

/*Design Pad*/
gStyle->SetOptStat(0);
gStyle->SetCanvasColor(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetPadBorderMode(0);
gStyle->SetPadColor(0);
gStyle->SetFrameBorderMode(0);

TCanvas* c1 = new TCanvas("c1", "c1", 500, 500);

TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.0001, 1.0, 1.0);

pad1->SetGrid();
pad1->SetLogy();
pad1->Draw();

/*Design Null Histogram*/
pad1->cd();

TH2F *null1 = new TH2F("null1","", 2, XMIN, XMAX, 2, 0.0000000001,YMAX);
null1->GetXaxis()->SetTitle(title_name);
null1->GetYaxis()->SetTitle(Form("Number of events / %3.1f%s",binwidth,unit));
null1->GetXaxis()->SetTitleOffset(1.0);
null1->GetYaxis()->SetTitleOffset(1.26);
null1->GetXaxis()->SetTitleSize(0.04);
null1->GetYaxis()->SetTitleSize(0.035);
null1->GetXaxis()->SetLabelSize(0.03);
null1->GetYaxis()->SetLabelSize(0.03);

/*Draw histogram*/
null1   ->Draw();
stkBkgs ->Draw("same");
hSignal1->Draw("same");
hSignal2->Draw("same");

/*Design Legend and Latex*/
TLegend *l0 = new TLegend(0.63,0.89,0.90,0.70);

l0->SetFillStyle(0);
l0->SetBorderSize(0);
l0->SetTextSize(0.03);

TLegendEntry* lS1 = l0->AddEntry(hSignal1,"VBF W' M=2TeV","l");       lS1->SetTextColor(1);
TLegendEntry* lS2 = l0->AddEntry(hSignal2,"VBF W' M=5TeV","l");       lS2->SetTextColor(1);
TLegendEntry* lB1 = l0->AddEntry(hw2j100to500,"W+2j","f");            lB1->SetTextColor(1);

l0->Draw();

pad1->cd();

TLatex latex;

latex.SetNDC();
latex.SetTextSize(0.04);
latex.SetTextAlign(11);

latex.DrawLatex(0.6,0.92,Form("%.1f ab^{-1} (14 TeV)", Lumi/1000000.0));
		
/*output*/
TString pngname=histname+dataname+".png"; c1->Print("Histogram/"+pngname);

}
