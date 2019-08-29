// tiny example

ℝ pow4(real Φ) // ℝ can be used, as can real to define a real variable or function. All UTF-8 Letters can be used as identifier.
{
    return Φ^4; // ^ is no binary XOR operator, but a power.
}

ℤ pow4(int z) // ℤ or int can be used to define an integer variable or function
{
    return z^4;
}

print "Φ^4 = ";
print pow4(5.0);
print '\n';
