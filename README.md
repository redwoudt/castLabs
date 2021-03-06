# castLabs
## Code Overview

The doxygen documents are available within the *documents* folder. <br />

The code is executed from *main.cpp* to either:<br />
1. run the general task, as per the assignment (calling *runBasicCase()*)<br />
2. run a set of unit tests (calling *runTests()*)<br />

The code structure is grouped into the following folders:<br />
1. **HTTP** - contains a class that provided a simple HTTP interface for making requests and receiving responses<br />
  (this class is dependant upon the POCO library being installed on the platform)<br />
2. **ImageDecoder** - class to decode and extract images from the XML content<br />
3. **Interfaces** - contains interfaces (in future), for now it just contains an abstract class to be implemened by Iso Media File Parser Classes<br />
4. **IsoBaseMediaParser** - contains 3 classes: a base class that defines the generic features and local string and HTTP specific classes. In the case that the blocks become too big for local storage, then the HTTP specific class becomes important, as this allows for downloading the content in chunks. <br />
5. **Mdat** - entry point for extracting block data from given URI. <br />
6. **pugixml** - contains code for XML image decoding. <br />
7. **Tests** - unit tests. <br />
8. **utils** - contains all utils. for it just contains logging. <br />

## Build Setup
### OSX
from castLabs root directory:<br />
1. create *build* directory (mkdir build); cd to build directory<br />
2. *cmake ..*<br />
(setup cmake)<br />
3. *make MdatExtractor*<br />
(run make specific to OSX platform)<br />
4. *./MdatExtractor /tmp/*<br />
(execute program)<br />

### Linux
from castLabs root directory:<br />
1. create *build* directory (mkdir build); cd to build directory<br />
2. *cmake ..*<br />
(setup cmake)<br />
3. *make MdatExtractor_Linux*<br />
(run make specific to OSX platform)<br />
4. *./MdatExtractor_Linux /tmp/*<br />
(execute program)<br />

## Example Run

```
Ferdis-MacBook-Pro:build fredelin$ ./MdatExtractor /tmp/
[13:10:33] [LOG-INFO] [runBasicCase:12] Starting MDAT Extractor
[13:10:33] [LOG-INFO] [runBasicCase:15] About to extract the following uri http://demo.castlabs.com/tmp/text0.mp4to /tmp/
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type moof and size 181
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type mfhd and size 16
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type traf and size 157
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type tfhd and size 24
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type trun and size 20
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type uuid and size 44
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type uuid and size 61
[13:05:18] [LOG-INFO] [displayBoxFound:92] Found box of type mdat and size 17908
[13:05:17] [LOG-INFO] [displayBlockData:60] Content of mdat box is: <?xml version="1.0" encoding="UTF-8"?><tt xml:lang="spa" xmlns="http://www.w3.org/ns/ttml" xmlns:tts="http://www.w3.org/ns/ttml#styling" xmlns:smpte="http://www.smpte-ra.org/schemas/2052-1/2010/smpte-tt" ><head>
<smpte:information smpte:mode="Enhanced" />
<styling>
<style xml:id="emb" tts:fontSize="4.1%" tts:fontFamily="monospaceSansSerif" />
<style xml:id="ttx" tts:fontSize="3.21%" tts:fontFamily="monospaceSansSerif"/>
<style xml:id="backgroundStyle" tts:fontFamily="proportionalSansSerif" tts:fontSize="18px" tts:textAlign="center" tts:origin="0% 66%" tts:extent="100% 33%" tts:backgroundColor="rgba(0,0,0,0)" tts:displayAlign="center" />
<style xml:id="speakerStyle" style="backgroundStyle" tts:color="white" tts:textOutline="black 1px" tts:backgroundColor="transparent" />
<style xml:id="textStyle" style="speakerStyle" tts:color="white" tts:textOutline="none" tts:backgroundColor="black" />
</styling><layout>
<region xml:id="full" tts:origin="0% 0%" tts:extent="100% 100%" tts:zIndex="1" />
<region xml:id="speaker" style="speakerStyle" tts:zIndex="1" />
<region xml:id="background" style="backgroundStyle" tts:zIndex="0" />
</layout>
<metadata>
<smpte:image xml:id="image001" imagetype="PNG" encoding="Base64">
iVBORw0KGgoAAAANSUhEUgAAAtAAAAHgCAYAAACMxVqsAAAO90lEQVR4nO3dy3XjRgJAUWnO7DsGZekM7CwVQ0egWekMTeP3gAIo0vcuuyH8ijZeQwXw/evr6w0AANjmP4/eAQAAeCYCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBAIKABACAQ0AAAEAhoAAAIBDQAAAQCGgAAAgENAACBgAYAgEBAAwBA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
</smpte:image>
<smpte:image xml:id="image002" imagetype="PNG" encoding="Base64">
iVBORw0KGgoAAAANSUhEUgAAAtAAAAHgCAYAAACMxVqsAAAQFUlEQVR4nO3dW3LbyAFAUTmVf69Bu5wdzOzSa/AKlC8nCosg+wKNB6VzqvxjQ+gGCJLXIAj9+Pj4eAMAAMb86+wJAADAKxHQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIa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
</smpte:image>
<smpte:image xml:id="image003" imagetype="PNG" encoding="Base64">
iVBORw0KGgoAAAANSUhEUgAAAtAAAAHgCAYAAACMxVqsAAAQFUlEQVR4nO3dW3LbyAFAUTmVf69Bu5wdzOzSa/AKlC8nCosg+wKNB6VzqvxjQ+gGCJLXIAj9+Pj4eAMAAMb86+wJAADAKxHQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIaAAACAQ0AAIGABgCAQEADAEAgoAEAIBDQAAAQCGgAAAgENAAABAIa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
</smpte:image>
</metadata></head>
<body><div>

<!-- image-based SMPTE-TT -->
	<p region="full" begin="00:00:00.000" end="00:00:02.000" smpte:backgroundImage="image003"></p>
</div></body></tt>


[13:05:18] [LOG-INFO] [write_to_file:141] writing to file /tmp/image001.png
[13:05:18] [LOG-INFO] [write_to_file:141] writing to file /tmp/image002.png
[13:05:18] [LOG-INFO] [write_to_file:141] writing to file /tmp/image003.png

```

## Testing
The code was tested on: <br />
1. Mac OS X El Capitan Version 10.11.6 <br />
2. Linux Mint 16 Cinnamon 64-bit <br />
3. TBC - windows platform <br />

The following tests should be completed later on: <br />
1. Test simulating exceptions <br />
2. Test different content strings, with different sequences of box types <br />
3. Test on more platforms <br />

## Git Checkin Process
The branch *FR_Mdat_Extractor* was created to do development in. The developed code was merged with *master* once completed. From the *master* branch a *release-1-0-0* branch was created for the official release.  

## Bonus Work
### Large MDAT Blocks
*CHUNK_SIZE* is defined within the code, which forces the content to be downloaded in chunks, if bigger than the allowed size. The chunk downloads are handled within *IsoBaseMediaHTTPParser*, using byte range HTTP requests. 

### Extracting Images from XML
For now, it is assumed that the whole mdat content is downloaded all at once. After extracting the mdat content into a string (*IsoBaseMediaFileParser::extractMdatBlock()*), the images are extracted within *ImageDecoder::extractImages()*. The file name is obtained from the *xml:id* attribute and the image type is obtained from the *imagetype* attribute. The actual encoded string is then extracted using *ImageDecoder* class.

## Future Work
Future work include: <br />
1. Complete testing. <br /> 
2. Add image extraction in chunks. <br /> 
3. Add support to input URI source to program. <br />
4. Support multiple types of images. <br />
