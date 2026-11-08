<h1>Aufgabe_0</h1>
<p>Empirical benchmark comparing functional programming paradigms and zero-cost abstractions in C++20</p>

<h2>Project description</h2>
<p>This project explores modern C++ standard library features, functional abstractions, and comparative timing measurements[span_2](start_span)[span_2](end_span):</p>
<ol>
  <li>Generates a vector of <code>n</code> random alphanumeric characters (case-insensitive)[span_3](start_span)[span_3](end_span).</li>
  <li>Inserts elements into a priority queue (<code>std::priority_queue</code>) with a custom case-insensitive comparator[span_4](start_span)[span_4](end_span).</li>
  <li>
    <dl>
      <dt>Implements and compares three distinct architectural styles[span_5](start_span)[span_5](end_span):</dt>
      <dd><b>Classical:</b> Imperative loops (<code>for</code>/<code>while</code>) without STL algorithms[span_6](start_span)[span_6](end_span).</dd>
      <dd><b>Functional:</b> Loop-free STL algorithms (<code>std::generate</code>, <code>std::for_each</code>) and custom struct functors[span_7](start_span)[span_7](end_span).</dd>
      <dd><b>Lambda:</b> In-place anonymous lambda expressions and deduced comparator types[span_8](start_span)[span_8](end_span).</dd>
    </dl>
  </li>
  <li>Measures vector filling and queue sorting latency in microseconds (μs)[span_9](start_span)[span_9](end_span).</li>
</ol>

<h2>Project files</h2>
<table>
  <tr>
    <th colspan="2">Aufgabe_0</th>
  </tr>
  <tr>
    <td>CMakeLists.txt</td>
    <td>CMake build configuration (C++20 standard)</td>
  </tr>
  <tr>
    <td>main.cpp</td>
    <td>Main application implementing all three functional variants[span_10](start_span)[span_10](end_span)</td>
  </tr>
  <tr>
    <td>README.md</td>
    <td>Project documentation</td>
  </tr>
</table>

<h2>Installation and launch</h2>
<ol>
  <b>
    <li>
      <dl>
        <dt>Clone the repository</dt>
        <dd>
          <code>git clone https://github.com/Kyoryuu-lab/Aufgabe_0.git</code>
        </dd>
        <dd>
          <code>cd Aufgabe_0</code>
        </dd>
      </dl>
    </li>
  </b>
  <b>
    <li>
      <dl>
        <dt>Build the project</dt>
        <dd>
          <code>cmake -B build -DCMAKE_BUILD_TYPE=Release</code>
        </dd>
        <dd>
          <code>cmake --build build --config Release</code>
        </dd>
      </dl>
    </li>
  </b>
  <b>
    <li>
      <dl>
        <dt>Launch the executable</dt>
        <dd>
          <code>./build/main</code>
        </dd>
      </dl>
    </li>
  </b>
</ol>

<h2>Example of console output</h2>
<samp>
  <p>
    Hello, Char World!<br />
    Enter the number of characters: 10<br />
    <br />
    --- 1. Classical Variant (Loops) ---<br />
    Fill vector used time was: 52 us<br />
    Vector: 1FQUfkYvry<br />
    Fill queue used time was: 35 us<br />
    Queue:  fFk1QruvyY<br />
    <br />
    --- 2. Functional Variant (Functors) ---<br />
    Fill vector used time was: 48 us<br />
    Vector: 9AkLoPqZtW<br />
    Fill queue used time was: 31 us<br />
    Queue:  9AkLoPqTWZ<br />
    <br />
    --- 3. Modern Lambda Variant ---<br />
    Fill vector used time was: 47 us<br />
    Vector: mNbVxZkLpA<br />
    Fill queue used time was: 30 us<br />
    Queue:  AkLlmNbPVZ<br />
  </p>
</samp>
