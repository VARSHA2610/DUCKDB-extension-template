# System architecture:

Metrics used:

-exact match
-f1
-precision
-distance
-nli
-semantics


select llmevaluate(gold,response) from openairesponse;
action:
1. reads the value row by row and uses those 2 values in the metrics
2. Store each metric's value in the row;

returns :

1. returns the whole table with all the metric values 




