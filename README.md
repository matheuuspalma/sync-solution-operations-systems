# sync-solution-operations-systems
The solutin to the "The Santa Claus problem"
Sistemas Operacionas - Universidade Federal do Rio de Janeiro

Git Commands:

- git clone <repository-name>

# to clone the repository to local

- git add <file-names> -p
  or
  git add . -p
  # "." means that you want add all files in the staged area
# add is the command that is used to add files to staged area
# staged area is a place the files were "approved" to go to be pushed

- git commit "Example of comment" -m

- git push origin <branch-name>
# push files to origin (remote)

- git pull origin <branch-name>
# pull files of the origin (remote) to your local

- git checkout -b feature/new_branch
or
- git branch feature/new_branch + git checkout feature/new_branch

# command to create and change your current branch