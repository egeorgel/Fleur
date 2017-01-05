#for i in `grep -r '^class' include | awk 'BEGIN {FS="[: ]"}{print $3}'` ; do
#    for nameFile in `find src -name "*.cpp"`; do
#        filename1=$(basename "$nameFile")
#        sed -e "/include/ ! s/$i/fleur::$i/" $nameFile > /tmp/$filename1
#        mv /tmp/$filename1 $nameFile
#    done
#done

#for i in `grep -r '^class' include | awk 'BEGIN {FS="[: ]"}{print $3}'` ; do
    for nameFile in `find include -name "*.h"`; do
        filename1=$(basename "$nameFile")
        awk '{
            if ($1 == "class") {
                print "namespace fleur {"
                print $0
            } else if ($1 == "#endif") {
                print "}"
                print $0
            }else {
                print $0
            }
        }' $nameFile > /tmp/$filename1
        mv /tmp/$filename1 $nameFile
    done
#done
