using namespace std;

void hist_cut(){

        gSystem->Load("/home/taebh/MG5_aMC_v2_6_1/ExRootAnalysis/libExRootAnalysis.so");

        TChain* inChain = new TChain("LHEF");
        inChain->Add("/home/taebh/workspace/MG5_aMC_v2_6_4/VBFWprime/gridpack/wjets14/condorOut/*.root");

        TClonesArray* particleTCA = new TClonesArray("TRootLHEFParticle");

        inChain->SetBranchAddress("Particle",&particleTCA);

	TH1F* ele_PT = new TH1F("ele_PT","ele_PT",100,0,200);

/****************************************************************************************************************************************/

	int totalN = inChain->GetEntries();
	int cnt_cut = 0;
	cout << totalN << endl;
	for(int eventLoop=0; eventLoop<totalN; eventLoop++){

		inChain->GetEntry(eventLoop);

		int cnt=4;

		TLorentzVector eleVec;
		TLorentzVector nueVec;
		TLorentzVector jet1Vec;
		TLorentzVector jet2Vec;

		for(int pLoop=0; pLoop<particleTCA->GetEntries(); pLoop++){

			TRootLHEFParticle* particlePtr = (TRootLHEFParticle*)particleTCA->At(pLoop);

			if((particlePtr->Status)!=1)continue;
			if(abs(particlePtr->PID)==11/*&&particlePtr->PT>200*/){eleVec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);cnt--;}
			if(abs(particlePtr->PID)==12/*&&particlePtr->PT>150*/){nueVec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);cnt--;}
			if((abs(particlePtr->PID)<5||particlePtr->PID==21)&&cnt==2){jet1Vec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);cnt--;continue;}
			if((abs(particlePtr->PID)<5||particlePtr->PID==21)&&cnt==1){jet2Vec.SetPxPyPzE(particlePtr->Px,particlePtr->Py,particlePtr->Pz,particlePtr->E);cnt--;}

		}

		TLorentzVector jjVec=jet1Vec+jet2Vec;
		TLorentzVector wVec=eleVec+nueVec;
	
		ele_PT->Fill(eleVec.Pt());
	
		if(cnt!=0)continue;
		if((eleVec.Pt())<=200)continue;
		if((nueVec.Pt())<=150)continue;
		if((jjVec.M())<=500)continue;
		if(abs((jet1Vec.Eta())-(jet1Vec.Eta()))<=2.5)continue;

		cnt_cut++;

	}

	cout << cnt_cut << endl;

	ele_PT->Draw();

}

