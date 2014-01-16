search='<In FileName=/nfs/dust/cms/user'
replace='<In FileName="/nfs/dust/cms/user'
for file in `find -name '*.xml'`; do
  grep "$search" $file &> /dev/null
  if [ $? -ne 0 ]; then
    echo "Search string not found in $file!"
  else
    sed -i "s!$search!$replace!" $file
  fi  
done