# Contribution guide


## Pull request
<ol>
    <li>
    First, stage your changes by using <code>git add &lt;changed_file&gt; </code> <br>
    Example: <code>git add /C++/my_code.cpp </code> <br>
    Do not use <code>git add .</code> because it will stage unnecessary files. A goode IDE can help you with this.
    </li>
    <li>
    Commit by using <code>git commit -m "My message"</code>. Give it a meaningful one such as "Fixed bug for input" instead of "Minor fix"
    </li>
    <li>
    Rebasing from main meaning you update your code. This is due to because during you work on your branch, other people
    have made updates. To do this, use <code>git rebase -i origin/main</code>. After that, type <code>:wq</code> and Enter.
    This is Vim syntax, ask me for more details about this step.
    </li>
    <li>
    Push your changes via <code>git push</code>.
    </li>
    <li>
    On the project page [Here](https://github.com/danny-cpp/QuantumPermutationPad). Click on Pull Request tab. Click on New Pull Request
    button, and create one from your branch to main.
    </li>
    <li>
    Ping on Discord to get it reviewed.
    </li>
</ol>

___

# Compile and execute guide

## For C++ code
<ol>
    <li>
    In the C++ directory, you will find the Makefile. In line 38, change it to <code>MODE := $(RELEASE)</code> or <code>MODE := $(DEBUG)</code> as you wish.
    Currently, we only support these 2 modes. Note that to use GDB to debug, you must use Debug profile.
    </li>
    <li>
    In the same directory use <code>make</code> the compile the code; <code>make clean</code> to clean everything.
    </li>
    <li>
    If the process run successfully, you will find a new binary in <code>bin/</code>. To execute, run <code>./bin/qpp.exe</code>.
    </li>
</ol>
