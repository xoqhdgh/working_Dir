source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530

cd /home/taebh/CMSSW_9_1_0_pre3/src
eval \`scramv1 runtime -sh\`
cd -

export LD_LIBRARY_PATH=/home/taebh/workspace/Delphes3.4.2:$LD_LIBRARY_PATH

export PYTHIA8=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/pythia8/223-mlhled2/
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH

case $1 in
dy)
dirarray=('dyjet500-1000' 'dyjet1000-2000' 'dyjet2000-3000' 'dyjet3000-4000' 'dyjet4000-5000' 'dyjet5000-6000' 'dyjet6000-inf')
;;
tt)
dirarray=('ttbarjet100-500' 'ttbarjet500-1000' 'ttbarjet1000-2000' 'ttbarjet2000-3000' 'ttbarjet3000-inf')
;;
wj)
dirarray=('wjets100-500' 'wjets500-1000' 'wjets1000-2000' 'wjets2000-3000' 'wjets3000-4000' 'wjets4000-5000' 'wjets5000-6000' 'wjets6000-inf')
;;
sg)
dirarray=('wprime1000' 'wprime2000' 'wprime3000' 'wprime4000' 'wprime5000' 'wprime6000')
;;
ww)
dirarray=('wwjet500-1000' 'wwjet1000-2000' 'wwjet2000-3000' 'wwjet3000-4000' 'wwjet4000-5000' 'wwjet5000-6000')
;;
wz)
dirarray=('wzjet500-1000' 'wzjet1000-2000' 'wzjet2000-3000' 'wzjet3000-4000' 'wzjet4000-5000' 'wzjet5000-6000' 'wzjet6000-inf')
;;
esac

for dir in ${dirarray[*]};do

	./make_hist_delphes_${2}.exe $dir &

done
