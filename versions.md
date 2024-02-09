
version 27 <br>
![1.png](screenshots%2F1.png)
    added bad demo of checking blocks of neighboring chunks for improved culling
    TODO: improve neighbor chunk culling  
    TODO: change grass side texture

version 26 <br>
    fixed texture atlas

version 25 <br>
    implemented texture atlas to keep using simple vbo with different block textures
    xTODO: every chunk but the first (or last??) gets wrong texture coordinates

version 23 <br>
    xTODO: blocktypes
    TODO: fix border faces of chunks being rendered
    TODO: lower initial loading time (std::arrays, rework functions, maybe multithreading)
    TODO later: procedural world generation
    TEST: all vbos with one vao
        works, no visible performance increase, will still use

version 22 <br>
    hardcoded bad worlgen in game.h
    TODO: implement proper worldgen
    xTODO: check noise (creates circular pattern


version 21 <br>
    sigsegv in worldgen, render_chunk() cant access vao and ebo ID

version 20 <br>
    SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT SEGFAULT
    wollen sie wissen was das scheiss problem war geliebte freunde:
        ich habe mich zu sehr auf copilot verlassen und der dumme hurensohn hat einfach copy paste gemacht anstatt nachzudenken
        und hat den gleichen chunk versucht 3 mal zu bauen anstatt 3 verschieden und ich wunder mich seit einem tag warum ich ein segfault kriege
        weil ich mich zu sehr auf copilot verlassen habe

    The Industrial Revolution and its consequences have been a disaster for the human race. They have greatly increased the
    life-expectancy of those of us who live in “advanced” countries, but they have destabilized society, have made life unfulfilling,
    have subjected human beings to indignities, have led to widespread psychological suffering (in the Third World to physical
    suffering as well) and have inflicted severe damage on the natural world. The continued development of technology will
    worsen the situation. It will certainly subject human being to greater indignities and inflict greater damage on the natural world,
    it will probably lead to greater social disruption and psychological suffering, and it may lead to increased physical suffering
    even in “advanced” countries.

version 17 <br>
    implemented "inefficient" culling
    xTODO: impelement world generation

version 16+ <br>
    implemented proper textures with render pipeline classes (VAO, VBO, EBO)
    TODO irgendwann: clean up render pipeline classes (everything is public)

version 16 <br>
    moved hardcoded texture implementation in chunk.h
    xTODO: implement proper textures with render pipeline classes

version 15 <br>
    hardcoded texture implementation in game.h

version 13 <br>
    xTODO later: cullling
    xTODO later later: reimplement textures
    moved build_Chunk() and render_Chunk() to chunk.h, by proper use of pointers

version 12_2_copy <br>
    5 days of work to get chunks working
    === going back to main branch

version 9_copy <br>
    rendern mit:
        new_render(): einzelnen VAO, VBO, EBO objekten
        temp_render(): alles in einer funktion

version 10 <br>
    WAS ICH BRAUCHE UM NICHT MEINEN VERSTAND ZU VERLIEREN
        CHUNK
        MESHING (+CULLING)

version 8 <br>
    !!! only 1 vao per chunk !!!
    xTODO now:
        culling
        mesh generation (?) => better chunks
    xTODO later:
        world generation

version 7+ <br>
    !clean version
    working:
        window creation
        render single cube
        texture
        camera
    xTODO:
        chunks
        world generation

version 7 <br>
    cameracameracameracameracameracameracameracamera

version 6 <br>
    input, ...
    no camera

version 5 <br>
    textures
    no input, no camera

version 4 <br>
    3d cube render
    no texture, no camera movement

version 3 <br>
    empty window

-- angefangen am 14.1.24 --
