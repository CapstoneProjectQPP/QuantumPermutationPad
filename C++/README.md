# Contribution guide

___

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