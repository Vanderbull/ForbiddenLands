Show all games in the game folder, sorted by rating, with some metadata:

```dataview
table time-played, length, rating, last-reviewed, tags,key3
from "games"
sort rating desc
```

