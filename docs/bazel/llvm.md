<!-- Generated with Stardoc: http://skydoc.bazel.build -->


Bazel rule for bringing **LLVM build definitions** into Bazel's sandbox environment

Brings **LLVM** into the scope of a bazel workspace.
This rule brings **LLVM** into the scope of a bazel workspace file primarily
designed for usage within **C++ binaries and libraries** (e.g. `cc_binary`,
`cc_library`). This is done by declaring `@llvm` as a dependency in your `BUILD`
files. With `@llvm` declared as a dependency you can then use LLVM classes, header
files, etc. in your project (e.g. `#include "llvm/IR/Value.h"`).

**Args**:

  _name_: A string. Name of the rule.

  _version_: A string. The version of LLVM to use (e.g. `15.0.4`, `14.0.0`, etc.) (Check
  https://github.com/llvm/llvm-project/releases for more details)

  _os_arch_: A string. The OS and CPU architecture combination to build for (e.g.
  `arm64-apple-darwin21.0`, `powerpc64le-linux-ubuntu-18.04.5`) (Check
  https://github.com/llvm/llvm-project/releases for more details)


<a id="llvm"></a>

## llvm

<pre>
llvm(<a href="#llvm-name">name</a>, <a href="#llvm-os_arch">os_arch</a>, <a href="#llvm-repo_mapping">repo_mapping</a>, <a href="#llvm-version">version</a>, <a href="#llvm-workspace_name">workspace_name</a>)
</pre>



**ATTRIBUTES**


| Name  | Description | Type | Mandatory | Default |
| :------------- | :------------- | :------------- | :------------- | :------------- |
| <a id="llvm-name"></a>name |  A unique name for this repository.   | <a href="https://bazel.build/concepts/labels#target-names">Name</a> | required |  |
| <a id="llvm-os_arch"></a>os_arch |  -   | String | optional | <code>"arm64-apple-darwin21.0"</code> |
| <a id="llvm-repo_mapping"></a>repo_mapping |  A dictionary from local repository name to global repository name. This allows controls over workspace dependency resolution for dependencies of this repository.&lt;p&gt;For example, an entry <code>"@foo": "@bar"</code> declares that, for any time this repository depends on <code>@foo</code> (such as a dependency on <code>@foo//some:target</code>, it should actually resolve that dependency within globally-declared <code>@bar</code> (<code>@bar//some:target</code>).   | <a href="https://bazel.build/rules/lib/dict">Dictionary: String -> String</a> | required |  |
| <a id="llvm-version"></a>version |  -   | String | optional | <code>"15.0.4"</code> |
| <a id="llvm-workspace_name"></a>workspace_name |  -   | String | required |  |


