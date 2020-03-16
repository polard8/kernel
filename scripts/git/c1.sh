#git filter-branch -f --index-filter 'git rm --cached --ignore-unmatch ./path/to/resource/*.VHD' --tag-name-filter cat -- --all    
git filter-branch -f --index-filter 'git rm --cached --ignore-unmatch ./path/to/resource/*.zip' --tag-name-filter cat -- --all    
git push origin --force --all    
git push origin --force --tags    


