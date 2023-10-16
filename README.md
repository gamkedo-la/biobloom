## Unreal Engine Build Helpers

1. Copy `env.example` to `.env`. This file contains one line which the path to your Unreal Engine 5.1
install directory. Make sure this is correct!

2. With the Unreal Editor closed, run `Build.bat`.

3. (Optional) If step 2 worked, you can set up a post-merge (runs when you run git pull) githook. To
do this, open `.git/hooks/post-merge.sh` and add the following:

```
#!/bin/sh
exec ../../Build.bat
```
