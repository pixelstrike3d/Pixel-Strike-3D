[![Pixel Strike 3D](PIxelStrike3DLogo.png)](#)

[![Version: 17.6.0](info_version.png)](#)
[![Platform: Android](info_platform.png)](#)


[![Copyright info](title_copyright.png)](#)

# All asset files belong to Pixel Strike 3D


# API Examples
Fetch Leaderboards
```python
from apis import PS3D

# Fill in your information accordingly:
player = PS3D(playFabId="...", token="...", device_id="...")

print(player.get_leaderboards())
```

Search Clans
```python
from apis import PS3D

# Fill in your information accordingly:
player = PS3D(playFabId="...", token="...", device_id="...")

print(player.search_clans("Example"))
```

Get Clan by ID
```python
from apis import PS3D

# Fill in your information accordingly:
player = PS3D(playFabId="...", token="...", device_id="...")

print(player.get_clan(1))
```
