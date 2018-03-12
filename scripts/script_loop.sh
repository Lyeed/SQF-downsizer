# This shell script can be use to create a duplicate of your project's folder
# The new folder will be loop through : .sqf and .hpp files size will be reduced
# The final stage consist of building the folder with AddonBuider and here you have your mission or addon 
# .git will also be removed from the final folder

# Path of your source folder.
# This folder will not be modified
source_folder="test_folder"

# New folder name. It will be created and modified.
# Pack this folder after process to obtain a clean pbo
dest_folder="test_pbo"

# Path to the downsize's executable
# If you place it in the same folder as the shell script just put 'downsize' otherwise put the full path
binary_file="C:/path/full/to/binary/downsize"
# binary_file="downsize"

## #########
## DO NOT EDIT BELOW UNLESS YOU KNOW WHAT YOU ARE DOING
## #########
if [ -d $dest_folder ]; then
	rm -rf $dest_folder
fi

cp -r $source_folder $dest_folder

if [ -d "$dest_folder/.git" ]; then
	rm -rf "$dest_folder/.git"	
fi

for f in $(find $dest_folder -name '*.sqf' -or -name '*.hpp' -or -name 'description.ext' -or -name 'config.cpp');
do 
	$binary_file $f $f;
done
