#include "TMath.h"

using namespace std;

void hist_cut(){

        gSystem->Load("/home/taebh/MG5_aMC_v2_6_1/ExRootAnalysis/libExRootAnalysis.so");

	TString dirname = "wjets_500Mjj_14Tev";

        TChain* inChain = new TChain("LHEF");
        inChain->Add("/home/taebh/workspace/MG5_aMC_v2_6_4/VBFWprime/gridpack/"+dirname+"/condorOut/*.root");

        TClonesArray* particleTCA = new TClonesArray("TRootLHEFParticle");

	TFile* outfile = new TFile(dirname+"_VBFcut.root","recreate");

        inChain->SetBranchAddress("Particle",&particleTCA);

	TH1F* PT_ele = new TH1F("PT_ele","PT_ele",10000,0,2000);
	TH1F* PT_nue = new TH1F("PT_nue","PT_nue",10000,0,2000);
	TH1F* Mt_ev = new TH1F("Mt_ev","Mt_ev",10000,0,10000);
	TH1F* ratio_ev = new TH1F("ratio_ev","ratio_ev",10000,0,100);
	TH1F* delta_Phi_ev = new TH1F("delta_Phi_ev","delta_Phi_ev",10000,0,4);

	TH1F* jets_PT = new TH1F("jets_PT","jets_PT",10000,0,7000);
	TH1F* jets_eta = new TH1F("jets_eta","jets_eta",10000,-6,6);
	TH1F* delta_Eta_jj = new TH1F("delta_Eta_jj","delta_Eta_jj",10000,0,20);
	TH1F* delta_Phi_jj = new TH1F("delta_Phi_jj","delta_Phi_jj",10000,0,3.2);
	TH1F* Mjj = new TH1F("Mjj","Mjj",10000,0,7000);
	TH1F* Zeppenfeld = new TH1F("Zeppenfeld","Zeppenfeld",10000,0,20);

        TH1F* delta_R_jj = new TH1F("delta_R_jj","delta_R_jj",100,0,200);
        TH1F* ratio_jj = new TH1F("ratio_jj","ratio_jj",100,0,200);
        TH1F* delta_R_ej1 = new TH1F("delta_R_ej1","delta_R_ej1",100,0,200);
        TH1F* delta_R_ej2 = new TH1F("delta_R_ej2","delta_R_ej2",100,0,200);
        TH1F* delta_R_wj1 = new TH1F("delta_R_wj1","delta_R_wj1",100,0,200);
        TH1F* delta_R_wj2 = new TH1F("delta_R_wj2","delta_R_wj2",100,0,200);

/****************************************************************************************************************************************/

	int totalN = inChain->GetEntries();
	int cnt_cut = 0;

	cout << totalN <<endl;

	for(int eventLoop=0; eventLoop<totalN; eventLoop++){

		inChain->GetEntry(eventLoop);

		int cnt=2;

		TLorentzVector eleVec;
		TLorentzVector nueVec;
		TLorentzVector jet1Vec;
		TLorentzVector jet2Vec;

		for(int pLoop=0; pLoop<particleTCA->GetEntries(); pLoop++){

			TRootLHEFParticle* particlePtr = (TRootLHEFParticle*)particleTCA->At(pLoop);

			if((particlePtr->Status)!=1)continue;
			if(abs(particlePtr->PID)==11)eleVec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);
			if(abs(particlePtr->PID)==12)nueVec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);
			if((abs(particlePtr->PID)<5||particlePtr->PID==21)&&cnt==2){jet1Vec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);cnt--;continue;}
			if((abs(particlePtr->PID)<5||particlePtr->PID==21)&&cnt==1){
				if(particlePtr->E>jet1Vec.E()){jet2Vec=jet1Vec;jet1Vec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);}
				else{jet2Vec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);}
				cnt--;
			}
		}

                TLorentzVector jjVec=jet1Vec+jet2Vec;
                TLorentzVector wVec=eleVec+nueVec;

		if(cnt!=0)continue;

		double ePt = eleVec.Pt();
		double vPt = nueVec.Pt();
		double j1Pt = jet1Vec.Pt();
		double j2Pt = jet2Vec.Pt();

		double ePhi = eleVec.Phi();
		double vPhi = nueVec.Phi();
		double j1Phi = jet1Vec.Phi();
		double j2Phi = jet2Vec.Phi();
		double wPhi = wVec.Phi();

		double eEta = eleVec.Eta();
		double j1Eta = jet1Vec.Eta();
		double j2Eta = jet2Vec.Eta();
		double wEta = wVec.Eta();

		double ev_delta_Phi = fabs(ePhi-vPhi);
		double jj_delta_Phi = fabs(j1Phi-j2Phi);
		double ej1_delta_Phi = fabs(ePhi-j1Phi);
		double wj1_delta_Phi = fabs(wPhi-j1Phi);
		double ej2_delta_Phi = fabs(ePhi-j2Phi);
		double wj2_delta_Phi = fabs(wPhi-j2Phi);
		double jj_delta_Eta = fabs(j1Eta-j2Eta);
                double ej1_delta_Eta = fabs(eEta-j1Eta);
                double wj1_delta_Eta = fabs(wEta-j1Eta);
                double ej2_delta_Eta = fabs(eEta-j2Eta);
                double wj2_delta_Eta = fabs(wEta-j2Eta);

		if(ev_delta_Phi>TMath::Pi())
			ev_delta_Phi = 2*(TMath::Pi())-ev_delta_Phi;
		
		if(jj_delta_Phi>TMath::Pi())
			jj_delta_Phi = 2*(TMath::Pi())-jj_delta_Phi;

                if(ej1_delta_Phi>TMath::Pi())
                        ej1_delta_Phi = 2*(TMath::Pi())-ej1_delta_Phi;

                if(wj1_delta_Phi>TMath::Pi())
                        wj1_delta_Phi = 2*(TMath::Pi())-wj1_delta_Phi;

                if(ej2_delta_Phi>TMath::Pi())
                        ej2_delta_Phi = 2*(TMath::Pi())-ej2_delta_Phi;

                if(wj2_delta_Phi>TMath::Pi())
                        wj2_delta_Phi = 2*(TMath::Pi())-wj2_delta_Phi;


		/*if(ePt<=200)continue;
		if(vPt<=150)continue;*/
		if((jjVec.M())<=500)continue;
		if(jj_delta_Eta<=2.5)continue;
		if(j1Pt<=60)continue;
		if(j2Pt<=50)continue;

		PT_ele->Fill(ePt);
		PT_nue->Fill(vPt);
		Mt_ev->Fill(2*ePt*vPt*(1-cos(ePhi-vPhi)));
		ratio_ev->Fill(ePt/vPt);
		delta_Phi_ev->Fill(ev_delta_Phi);

		jets_PT->Fill(j1Pt);
                jets_PT->Fill(j2Pt);
		jets_eta->Fill(j1Eta);
                jets_eta->Fill(j2Eta);
		delta_Eta_jj->Fill(jj_delta_Eta);
		delta_Phi_jj->Fill(jj_delta_Phi);
		Mjj->Fill(jjVec.M());
		Zeppenfeld->Fill(fabs(wEta-(j1Eta+j2Eta)/2));

		delta_R_jj->Fill(sqrt(jj_delta_Eta*jj_delta_Eta+jj_delta_Phi*jj_delta_Phi));
		ratio_jj->Fill(j1Pt/j2Pt);
		delta_R_ej1->Fill(sqrt(ej1_delta_Eta*ej1_delta_Eta+ej1_delta_Phi*ej1_delta_Phi));
		delta_R_ej2->Fill(sqrt(ej2_delta_Eta*ej2_delta_Eta+ej2_delta_Phi*ej2_delta_Phi));
		delta_R_wj1->Fill(sqrt(wj1_delta_Eta*wj1_delta_Eta+wj1_delta_Phi*wj1_delta_Phi));
		delta_R_wj2->Fill(sqrt(wj2_delta_Eta*wj2_delta_Eta+wj2_delta_Phi*wj2_delta_Phi));
		
		cnt_cut++;	
	}
	
	cout << cnt_cut << endl;

	cout << PT_ele->GetMinimum() << " " << PT_ele->GetMaximum() << endl;
        cout << PT_nue->GetMinimum() << " " << PT_nue->GetMaximum() << endl;
        cout << Mt_ev->GetMinimum() << " " << Mt_ev->GetMaximum() << endl;
        cout << ratio_ev->GetMinimum() << " " << ratio_ev->GetMaximum() << endl;
        cout << delta_Phi_ev->GetMinimum() << " " << delta_Phi_ev->GetMaximum() << endl;
        cout << jets_PT->GetMinimum() << " " << jets_PT->GetMaximum() << endl;
        cout << jets_eta->GetMinimum() << " " << jets_eta->GetMaximum() << endl;
        cout << delta_Eta_jj->GetMinimum() << " " << delta_Eta_jj->GetMaximum() << endl;
        cout << delta_Phi_jj->GetMinimum() << " " << delta_Phi_jj->GetMaximum() << endl;
        cout << Mjj->GetMinimum() << " " << Mjj->GetMaximum() << endl;
        cout << Zeppenfeld->GetMinimum() << " " << Zeppenfeld->GetMaximum() << endl;

	outfile->Write();

}
