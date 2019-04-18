void draw_signifi() {

/*Physics Parameters*/
double Lumi = 1000000.0;

//long double xsecSignal=7.86413203891e-03; TString plotname = "1000mass";
//long double xsecSignal=6.02158250669e-04; TString plotname = "2000mass";
//long double xsecSignal=8.0034493626e-05;  TString plotname = "3000mass";
//long double xsecSignal=1.21682024511e-05; TString plotname = "4000mass";
//long double xsecSignal=1.89757563679e-06; TString plotname = "5000mass";
long double xsecSignal=2.88776020804e-07; TString plotname = "6000mass";

long double xsecw2j100to500  =22.4645492;
long double xsecw2j500to1000 =0.220401086;
long double xsecw2j1000to2000=0.00847007776;
long double xsecw2j2000to3000=6.160953643e-05;
long double xsecw2j3000to4000=6.5935273893e-07;
long double xsecw2j4000to5000=5.62906155243e-09;
long double xsecw2j5000to6000=2.39018329425e-11;
long double xsecw2j6000toinf =7.29251198043e-15;

int NSignal       =1000000;
int Nw2j100to500  =1000000;
int Nw2j500to1000 =1000000;
int Nw2j1000to2000=1000000;
int Nw2j2000to3000=1000000;
int Nw2j3000to4000=1000000;
int Nw2j4000to5000=1000000;
int Nw2j5000to6000=1000000;
int Nw2j6000toinf =1000000;

TString dataname = "_VBFcut";

/*Read Draft Rootfile*/
TFile* fSignal        = TFile::Open("Signal/signal_"+plotname+dataname+".root");

TFile* fw2j100to500   = TFile::Open("W2jet/wjets_500Mjj_4mom100to500"+dataname+".root");
TFile* fw2j500to1000  = TFile::Open("W2jet/wjets_500Mjj_4mom500to1000"+dataname+".root");
TFile* fw2j1000to2000 = TFile::Open("W2jet/wjets_500Mjj_4mom1000to2000"+dataname+".root");
TFile* fw2j2000to3000 = TFile::Open("W2jet/wjets_500Mjj_4mom2000to3000"+dataname+".root");
TFile* fw2j3000to4000 = TFile::Open("W2jet/wjets_500Mjj_4mom3000to4000"+dataname+".root");
TFile* fw2j4000to5000 = TFile::Open("W2jet/wjets_500Mjj_4mom4000to5000"+dataname+".root");
TFile* fw2j5000to6000 = TFile::Open("W2jet/wjets_500Mjj_4mom5000to6000"+dataname+".root");
TFile* fw2j6000toinf  = TFile::Open("W2jet/wjets_500Mjj_4mom6000toinf"+dataname+".root");
                                     
/*Histogram list in Rootfile*/
TString histname = "Centrality";

/*Get Histogram & Normalizing*/
TH1F* hSignal        = (TH1F*)fSignal       ->Get(histname); hSignal      ->Scale(xsecSignal*Lumi/NSignal);
TH1F* hw2j100to500   = (TH1F*)fw2j100to500  ->Get(histname); hw2j100to500  ->Scale(xsecw2j100to500*Lumi/Nw2j100to500);
TH1F* hw2j500to1000  = (TH1F*)fw2j500to1000 ->Get(histname); hw2j500to1000 ->Scale(xsecw2j500to1000*Lumi/Nw2j500to1000);
TH1F* hw2j1000to2000 = (TH1F*)fw2j1000to2000->Get(histname); hw2j1000to2000->Scale(xsecw2j1000to2000*Lumi/Nw2j1000to2000);
TH1F* hw2j2000to3000 = (TH1F*)fw2j2000to3000->Get(histname); hw2j2000to3000->Scale(xsecw2j2000to3000*Lumi/Nw2j2000to3000);
TH1F* hw2j3000to4000 = (TH1F*)fw2j3000to4000->Get(histname); hw2j3000to4000->Scale(xsecw2j3000to4000*Lumi/Nw2j3000to4000);
TH1F* hw2j4000to5000 = (TH1F*)fw2j4000to5000->Get(histname); hw2j4000to5000->Scale(xsecw2j4000to5000*Lumi/Nw2j4000to5000);
TH1F* hw2j5000to6000 = (TH1F*)fw2j5000to6000->Get(histname); hw2j5000to6000->Scale(xsecw2j5000to6000*Lumi/Nw2j5000to6000);
TH1F* hw2j6000toinf  = (TH1F*)fw2j6000toinf ->Get(histname); hw2j6000toinf ->Scale(xsecw2j6000toinf*Lumi/Nw2j6000toinf);

long double Ns,Nbg,significance;
double x[501];
double y[501];
double x2[179];
double y2[179];
int cnt=0;

for(int i=0; i<10000;i+=10){

	Nbg=hw2j100to500   ->Integral(i,10000);
	Nbg+=hw2j500to1000 ->Integral(i,10000);
	Nbg+=hw2j1000to2000->Integral(i,10000);
	Nbg+=hw2j2000to3000->Integral(i,10000);
	Nbg+=hw2j3000to4000->Integral(i,10000);
	Nbg+=hw2j4000to5000->Integral(i,10000);
	Nbg+=hw2j5000to6000->Integral(i,10000);
	Nbg+=hw2j6000toinf ->Integral(i,10000);
	Ns=hSignal->Integral(i,10000);

	if(Nbg==0.0)continue;

	x[i/10]=i/1000.0;
	y[i/10]=double(Ns/sqrt(Nbg));

	cnt++;
}

cout<<cnt<<endl;

for(int i=0;i<179;i++)
{
	x2[i]=x[i];
	y2[i]=y[i];
}

TCanvas *c = new TCanvas();

c->cd();
TGraph *g = new TGraph(179,x2,y2);

g->Draw("ALP");
g->SetMarkerStyle(20);

c->Print("Plot/"+plotname+"_"+histname+dataname+".png");

}

