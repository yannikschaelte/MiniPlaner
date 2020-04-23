# Contribute to MiniPlaner


We are happy about contributions to MiniPlaner in any form, be it new 
functionality, documentation, bug reports, feature requests, or anything else.

If you would like to contribute to MiniPlaner, a good start is looking for 
[issues](https://github.com/yannikschaelte/MiniPlaner/issues), in particular 
ones marked `good first issue` or `help wanted`. For other ideas or questions, 
just post an issues.


## Branches / releases

MiniPlaner roughly follows the
[git-flow](https://nvie.com/posts/a-successful-git-branching-model/). All new
contributions are merged into `develop`. These changes are regularly merged
into `master` as new releases. For release versioning we are trying to follow
[semantic versioning](https://semver.org/).

We try to keep a clean git history. Therefore, feature pull requests are
squash-merged to `develop`. Merging of release branches to master is done via
merge commits.


## When starting to work on some issue

When starting to work on some Github issue, please assign yourself to let other
developers know that you are working on it to avoid duplicate work. If the
respective issue is not completely clear, it is generally a good idea to ask
for clarification before starting to work on it.

If you want to work on something new, please create a Github issue first.


## Code contributions

When making code contributions, please follow our style guide and the process
described below:

* Check if you agree to release your contribution under the conditions provided
  in [`LICENSE`](LICENSE). By opening a pull requests you confirm us that you do agree.
  
* Start a new branch from `develop` (on your fork, or at the main
  repository if you have access)

* Implement your changes

* Submit a pull request to the `develop` branch

* Make sure your code is documented appropriately

* Make sure your code is compatible with C++11 and `gcc`

* When adding new functionality, please also provide test cases

* Write meaningful commit messages

* When all tests are passing and you think your code is ready to merge,
  request a code review from the code owners

* Wait for feedback. If you do not receive feedback to your pull request within
  a week, please give us a friendly reminder.


### Style guide


#### General

* All files and functions should come with file-level and function-level
  documentation.
  
* All new functionality should be covered by unit or integration tests. Runtime
  of those tests should be kept as short as possible. 
