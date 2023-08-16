# custom-square-root-impl
Uses the square root approximation method, but with increased accuracy.  \
The approximation method:  \
r(x) = closest perfect square function (impl in code) (can be impl in graphing calculator with floor(sqrt(x)))  \
f(x) = r(x) + ((x - r(x)^2) / r(x)) / 2  \
\
where f(x) is a function for the approximate square root of x.  \
Graphing f(x) and y = sqrt(x) shows that as x increases, f(x) converges to sqrt(x), and has higher accuracy.  \
Using this logic, tranforming f(x) to f(x * k) / sqrt(k), where k is a constant, has f(x) converge to sqrt(x) sooner compared to before the transformation.  \
Since k can be any number, and the transformation calls for a square root, we can use powers of 2 and bitwise shifting in the code to mimick a square root.  \
