## Sync-solution-operations-systems
The solutin to the "The Santa Claus problem"
Sistemas Operacionas - Universidade Federal do Rio de Janeiro

## Git Commands:

  - To clone the repository to local

  _git clone <repository-name>_

  

  - To ad to staged area

 _git add <file-names> -p_ or _git add . -p_

 

_"." means that you want add all files in the staged area_
_add is the command that is used to add files to staged area_
_staged area is a place the files were "approved" to go to be pushed_


- To commit
  
_git commit "Example of comment" -m_


- To push files to origin (remote)
  
_git push origin <branch-name>_


- To pull files of the origin (remote) to your local
  
_git pull origin <branch-name>_


- Command to create and change your current branch

  _git checkout -b feature/new_branch_
                 or
  _git branch feature/new_branch + git checkout feature/new_branch_
