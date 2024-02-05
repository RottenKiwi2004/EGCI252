# Multiple Processes

### <center><u>Program Address Space</u></center>

<style>
    td.memory {
        border: 1px white solid !important;
        display: flex!important;
        flex-direction: column;
        align-items: center;
        justify-content: center;
    }
    td.blank {
        font-size: x-large;
        display: flex!important;
        flex-direction: column;
        align-items: center;
        justify-content: center;
    }
    td.explanation {
        border-left: 1px #ffffff55 dashed!important;
    }
    tr, td {
        border: none !important;
    }
</style>
<center>
    <table>
        <tr>
            <td class="memory" id=stack>Stack segment</td>
            <td class="indicator">variable size</td>
            <td class="explanation">Parameters, Return addresses, Local variables</td>
        </tr>
        <tr>
            <td class="memory blank">↓</td>
        </tr>
        <tr>
            <td class="memory blank">↑</td>
        </tr>
        <tr>
            <td class="memory">Heap segment</td>
            <td class="indicator">variable size</td>
            <td class="explanation">Dynamic variables; malloc(), free()</td>
        </tr>
        <tr>
            <td class="memory">BSS segment</td>
            <td class="indicator">fixed size</td>
            <td class="explanation">Uninitialised global and static variables</td>
        </tr>
        <tr>
            <td class="memory">DATA segment</td>
            <td class="indicator">fixed size</td>
            <td class="explanation">Initialised global and static variables</td>
        </tr>
        <tr>
            <td class="memory">TEXT segment</td>
            <td class="indicator">fixed size</td>
            <td class="explanation">Program code</td>
        </tr>
    </table>
</center>

## Task State
- `TASK_RUNNING` : running / waiting to be executed
- `TASK_INTERRUPTIBLE` : sleeping / suspended process, awakened by signal
- `TASK_STOPPED` : process stopped (by debugger / Ctrl-Z)
- `TASK_ZOMBIE` : "walking dead" waiting for `wait()` call from parent
- `TASK_UNINTERRUPTIBLE` : task should not be interrupted by a signal (performing crucial task)

## Process Attributes

### <u>PID & PPID</u>
