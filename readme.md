# System architecture:

Metrics used:

exact match
f1
precesion
distance
nli
semantics


select llmevaluate(gold,response) from openairesponse;
action:
1. reads the value row by row and use those 2 values in the metrics
2. Store each metrics value to the row;

returns :

1. returns the whole table with all the metrics value 

Analytics :


