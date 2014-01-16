#!/bin/bash

#Select here the list name
idlist="TTJets_HadronicMGDecays_8TeV-madgraph_ntuplewriter_ttbsm_53_plusprunedcfg"

#Select here the directory
directory="/scratch/hh/dust/naf/cms/user/hoeing/Samples_TTBSM53/TTJets_HadronicMGDecays_8TeV-madgraph_ntuplewriter_ttbsm_53_plusprunedcfg.list/"

#Select number > 0 if wants lo limit the amount of available files
numberwantedfiles=0

#Eventually select the root name of the files if different from the list name
rootfilename=$(echo ${idlist})

ls $directory/${rootfilename}* > listoffiles

numberfiles=$(wc -l listoffiles | awk '{print $1}')

if [ $numberwantedfiles -gt 0 ]; then

let "numberfiles=numberwantedfiles"

fi

echo "Listing ${numberfiles} files for the id ${rootfilename}"

if [ -e ${idlist}.xml ]; then
mv ${idlist}.xml ${idlist}.xml.old
fi

i=1

while [ $i -le $numberfiles ]; do

filename=$(cut -d'
' -f$i listoffiles | awk '{print $1}')

echo "file ${i} with name ${filename}"

echo  "<In FileName=\"${filename}\"  Lumi=\"0.0\"/>" >> ${idlist}.xml

let "i=i + 1"
done

rm -f listoffiles
