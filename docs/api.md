# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`_ASSET`](#struct__ASSET) | 
`struct `[`_ASSET_PACK`](#struct__ASSET__PACK) | 
`struct `[`_CAMERA`](#struct__CAMERA) | 
`struct `[`_DRAWSURFACE`](#struct__DRAWSURFACE) | 
`struct `[`_SHADER`](#struct__SHADER) | 
`struct `[`_TEXTURE`](#struct__TEXTURE) | 
`struct `[`_TEXTURE_PACK`](#struct__TEXTURE__PACK) | 
`struct `[`BEHAVE`](#structBEHAVE) | 
`struct `[`BEZIER`](#structBEZIER) | 
`struct `[`FRACTAL`](#structFRACTAL) | 
`struct `[`LIGHTSOURCE`](#structLIGHTSOURCE) | 
`struct `[`LIGHTSOURCE_DIR`](#structLIGHTSOURCE__DIR) | 
`struct `[`LIGHTSOURCE_POINT`](#structLIGHTSOURCE__POINT) | 
`struct `[`MAZE`](#structMAZE) | 
`struct `[`MAZE_WALLS`](#structMAZE__WALLS) | 
`struct `[`MODEL`](#structMODEL) | 
`struct `[`MOUSE`](#structMOUSE) | 
`struct `[`PMOUSE`](#structPMOUSE) | 
`struct `[`SHADER_DESCRIPTOR`](#structSHADER__DESCRIPTOR) | 
`struct `[`TERRAIN`](#structTERRAIN) | 
`struct `[`vec3_pack`](#structvec3__pack) | 
`struct `[`WORLD`](#structWORLD) | 
`union `[`COLOR`](#unionCOLOR) | 
`union `[`ICOLOR`](#unionICOLOR) | 
`union `[`uvect2_8`](#unionuvect2__8) | 
`union `[`vect`](#unionvect) | 

# struct `_ASSET` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`width`](#struct__ASSET_1a9858f1d2d80d257e6b5a0b45b320c004) | 
`public int `[`height`](#struct__ASSET_1a63e0232bd6a1986e2fe213ee7d5caf18) | 
`public int `[`size`](#struct__ASSET_1abc2055948d13ddc12e282f279c0a8afb) | 
`public GLenum `[`format`](#struct__ASSET_1ad55c77d9238a7f9dcd1680a3d166b967) | 
`public void * `[`data`](#struct__ASSET_1ae66aa02bb11d27c7385c06a1e49cc4f5) | 

## Members

#### `public int `[`width`](#struct__ASSET_1a9858f1d2d80d257e6b5a0b45b320c004) 

#### `public int `[`height`](#struct__ASSET_1a63e0232bd6a1986e2fe213ee7d5caf18) 

#### `public int `[`size`](#struct__ASSET_1abc2055948d13ddc12e282f279c0a8afb) 

#### `public GLenum `[`format`](#struct__ASSET_1ad55c77d9238a7f9dcd1680a3d166b967) 

#### `public void * `[`data`](#struct__ASSET_1ae66aa02bb11d27c7385c06a1e49cc4f5) 

# struct `_ASSET_PACK` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`flags`](#struct__ASSET__PACK_1ac486aadf1ff1c7d89583d0502eea4c60) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`index`](#struct__ASSET__PACK_1a66b5750e9f6f6be5c7795aaffb7ebfdc) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`tex`](#struct__ASSET__PACK_1a69e5c66272e30bfc190178ff44966270) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`norm`](#struct__ASSET__PACK_1a51dd73914763e5ffcb4cd29ee4124d3f) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`disp`](#struct__ASSET__PACK_1af9ea4ba635c91796587881e56374a282) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`occl`](#struct__ASSET__PACK_1a2d6be1c1becf74ac83bd5e1fbb0062ed) | 
`public union `[`_ASSET_PACK`](#struct__ASSET__PACK)` `[``](#struct__ASSET__PACK_1a21ce8fbdab615657496221c49267f932) | 

## Members

#### `public unsigned int `[`flags`](#struct__ASSET__PACK_1ac486aadf1ff1c7d89583d0502eea4c60) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`index`](#struct__ASSET__PACK_1a66b5750e9f6f6be5c7795aaffb7ebfdc) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`tex`](#struct__ASSET__PACK_1a69e5c66272e30bfc190178ff44966270) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`norm`](#struct__ASSET__PACK_1a51dd73914763e5ffcb4cd29ee4124d3f) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`disp`](#struct__ASSET__PACK_1af9ea4ba635c91796587881e56374a282) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`occl`](#struct__ASSET__PACK_1a2d6be1c1becf74ac83bd5e1fbb0062ed) 

#### `public union `[`_ASSET_PACK`](#struct__ASSET__PACK)` `[``](#struct__ASSET__PACK_1a21ce8fbdab615657496221c49267f932) 

# struct `_CAMERA` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`pos`](#struct__CAMERA_1a1ce19e91c7257956ba4f0a3d644552fe) | 
`public vec3 `[`rot`](#struct__CAMERA_1a07bdbb668eb67f0e7994ea487803e1e9) | 
`public float `[`fov`](#struct__CAMERA_1a7cd9cfccc4ba98a423f04fa791772651) | 
`public float `[`ratio`](#struct__CAMERA_1a24365eccf46757d868e64e105e1a939b) | 
`public float `[`zoom`](#struct__CAMERA_1ab920885b1452571eaa716f6d338d6131) | 
`public int `[`type`](#struct__CAMERA_1a6d91edf304b6283ead66f94f591e3302) | 
`public mat4 `[`viewmat`](#struct__CAMERA_1a61395d53e72f300f2e451eb9b67283b5) | 
`public float `[`raw`](#struct__CAMERA_1af1d36cf38b12add2ee4a160b9cd9d710) | 
`public union `[`_CAMERA`](#struct__CAMERA)` `[``](#struct__CAMERA_1a723df633b03d30e1d296f64fbfb6081b) | 
`public mat4 `[`mod_viewmat`](#struct__CAMERA_1a8c9c8479021f38745fc921afeaa9f8c9) | 
`public int `[`swidth`](#struct__CAMERA_1a1c0061bdd7dd1aff84eb19b8d590aa96) | 
`public int `[`sheight`](#struct__CAMERA_1aa8a7cee7bda3e64b20368cd28b438e2b) | 
`public vec3 `[`wmin`](#struct__CAMERA_1a8c947adfba9c8984474cf3c94232ca5c) | 
`public vec3 `[`wmax`](#struct__CAMERA_1a11a943013c533ba5412b21204d0c7dcd) | 

## Members

#### `public vec3 `[`pos`](#struct__CAMERA_1a1ce19e91c7257956ba4f0a3d644552fe) 

#### `public vec3 `[`rot`](#struct__CAMERA_1a07bdbb668eb67f0e7994ea487803e1e9) 

#### `public float `[`fov`](#struct__CAMERA_1a7cd9cfccc4ba98a423f04fa791772651) 

#### `public float `[`ratio`](#struct__CAMERA_1a24365eccf46757d868e64e105e1a939b) 

#### `public float `[`zoom`](#struct__CAMERA_1ab920885b1452571eaa716f6d338d6131) 

#### `public int `[`type`](#struct__CAMERA_1a6d91edf304b6283ead66f94f591e3302) 

#### `public mat4 `[`viewmat`](#struct__CAMERA_1a61395d53e72f300f2e451eb9b67283b5) 

#### `public float `[`raw`](#struct__CAMERA_1af1d36cf38b12add2ee4a160b9cd9d710) 

#### `public union `[`_CAMERA`](#struct__CAMERA)` `[``](#struct__CAMERA_1a723df633b03d30e1d296f64fbfb6081b) 

#### `public mat4 `[`mod_viewmat`](#struct__CAMERA_1a8c9c8479021f38745fc921afeaa9f8c9) 

#### `public int `[`swidth`](#struct__CAMERA_1a1c0061bdd7dd1aff84eb19b8d590aa96) 

#### `public int `[`sheight`](#struct__CAMERA_1aa8a7cee7bda3e64b20368cd28b438e2b) 

#### `public vec3 `[`wmin`](#struct__CAMERA_1a8c947adfba9c8984474cf3c94232ca5c) 

#### `public vec3 `[`wmax`](#struct__CAMERA_1a11a943013c533ba5412b21204d0c7dcd) 

# struct `_DRAWSURFACE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`asset`](#struct__DRAWSURFACE_1ae3d760baf9c3de0f41891451badf822c) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` `[`texture`](#struct__DRAWSURFACE_1a524729c15474780f361d5b506f6657a4) | 
`public `[`DRAWSURFACE_CALLBACK`](#drawsurface_8h_1a89e4f192a8301518c984543e748213e2)` `[`callback`](#struct__DRAWSURFACE_1a6405fa0740064bf6bb675728c14dcfaa) | 
`public void * `[`data`](#struct__DRAWSURFACE_1af0d03219037b5cdc0f8660d0ae3f1f62) | 
`public GLuint `[`framebuffer`](#struct__DRAWSURFACE_1a88eae23ea6a416df0312b4b70a7a979c) | 
`public GLuint `[`depthbuffer`](#struct__DRAWSURFACE_1aa36a07bd58d1b4f9c95b8a1c1003e52b) | 

## Members

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` `[`asset`](#struct__DRAWSURFACE_1ae3d760baf9c3de0f41891451badf822c) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` `[`texture`](#struct__DRAWSURFACE_1a524729c15474780f361d5b506f6657a4) 

#### `public `[`DRAWSURFACE_CALLBACK`](#drawsurface_8h_1a89e4f192a8301518c984543e748213e2)` `[`callback`](#struct__DRAWSURFACE_1a6405fa0740064bf6bb675728c14dcfaa) 

#### `public void * `[`data`](#struct__DRAWSURFACE_1af0d03219037b5cdc0f8660d0ae3f1f62) 

#### `public GLuint `[`framebuffer`](#struct__DRAWSURFACE_1a88eae23ea6a416df0312b4b70a7a979c) 

#### `public GLuint `[`depthbuffer`](#struct__DRAWSURFACE_1aa36a07bd58d1b4f9c95b8a1c1003e52b) 

# struct `_SHADER` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public GLuint `[`program`](#struct__SHADER_1a3ce28c4ac154bbe7b830e70ded51dc8c) | 
`public `[`SHADER_USE_CALL`](#shader_8h_1a6f78246893f414a86961c0c85c6601f3)` `[`callback`](#struct__SHADER_1a8fd5003254db7231cdb7cdcdee05853d) | 
`public `[`SHADER_DRAW_CALL`](#shader_8h_1a6c78a3884c5b82382032dda2e8ab40d3)` `[`drawcall`](#struct__SHADER_1a59022cff969c9e4c2e92c6ef74c08d79) | 
`public void * `[`data`](#struct__SHADER_1a9689436fa889f6bf7d16db0d868ce575) | 
`public int `[`drawtype`](#struct__SHADER_1a0ed18362cc1babae4782384bfffea73d) | 
`public int `[`meshtype`](#struct__SHADER_1a694d5b061ad3308e0ee68e06b0b30d3b) | 
`public GLint `[`vert_pos_loc`](#struct__SHADER_1aec2b30257520a81b7aa5a74edf1aebfa) | 
`public GLint `[`vert_norm_loc`](#struct__SHADER_1a226f6adee0c0d0a4ca35f505437f592a) | 
`public GLint `[`vert_tex_loc`](#struct__SHADER_1a59ee5d43d0c03405f1a35f5a2d5b6dee) | 
`public GLint `[`attrib_loc`](#struct__SHADER_1ab00cd99923907329ae20707e51cef4c1) | 
`public union `[`_SHADER`](#struct__SHADER)` `[``](#struct__SHADER_1a5d573398a17e0ea0f9af5c78ff576c24) | 
`public GLint `[`u_mod_mat_loc`](#struct__SHADER_1ab837887ef9918c7ffc2e1b9d745fc6f0) | 
`public GLint `[`u_norm_mat_loc`](#struct__SHADER_1aceab994a26906b78f772837aca97585b) | 
`public GLint `[`u_color_loc`](#struct__SHADER_1a217de0f78174b5b27c58b3c6e41ab273) | 
`public GLint `[`u_light_norm_loc`](#struct__SHADER_1aed3c46b3b6115a7942fdd4c1ce7e688a) | 
`public GLint `[`u_light_map_loc`](#struct__SHADER_1a1fee55fe3faff759bd1c8619d8f28260) | 

## Members

#### `public GLuint `[`program`](#struct__SHADER_1a3ce28c4ac154bbe7b830e70ded51dc8c) 

#### `public `[`SHADER_USE_CALL`](#shader_8h_1a6f78246893f414a86961c0c85c6601f3)` `[`callback`](#struct__SHADER_1a8fd5003254db7231cdb7cdcdee05853d) 

#### `public `[`SHADER_DRAW_CALL`](#shader_8h_1a6c78a3884c5b82382032dda2e8ab40d3)` `[`drawcall`](#struct__SHADER_1a59022cff969c9e4c2e92c6ef74c08d79) 

#### `public void * `[`data`](#struct__SHADER_1a9689436fa889f6bf7d16db0d868ce575) 

#### `public int `[`drawtype`](#struct__SHADER_1a0ed18362cc1babae4782384bfffea73d) 

#### `public int `[`meshtype`](#struct__SHADER_1a694d5b061ad3308e0ee68e06b0b30d3b) 

#### `public GLint `[`vert_pos_loc`](#struct__SHADER_1aec2b30257520a81b7aa5a74edf1aebfa) 

#### `public GLint `[`vert_norm_loc`](#struct__SHADER_1a226f6adee0c0d0a4ca35f505437f592a) 

#### `public GLint `[`vert_tex_loc`](#struct__SHADER_1a59ee5d43d0c03405f1a35f5a2d5b6dee) 

#### `public GLint `[`attrib_loc`](#struct__SHADER_1ab00cd99923907329ae20707e51cef4c1) 

#### `public union `[`_SHADER`](#struct__SHADER)` `[``](#struct__SHADER_1a5d573398a17e0ea0f9af5c78ff576c24) 

#### `public GLint `[`u_mod_mat_loc`](#struct__SHADER_1ab837887ef9918c7ffc2e1b9d745fc6f0) 

#### `public GLint `[`u_norm_mat_loc`](#struct__SHADER_1aceab994a26906b78f772837aca97585b) 

#### `public GLint `[`u_color_loc`](#struct__SHADER_1a217de0f78174b5b27c58b3c6e41ab273) 

#### `public GLint `[`u_light_norm_loc`](#struct__SHADER_1aed3c46b3b6115a7942fdd4c1ce7e688a) 

#### `public GLint `[`u_light_map_loc`](#struct__SHADER_1a1fee55fe3faff759bd1c8619d8f28260) 

# struct `_TEXTURE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public GLuint `[`id`](#struct__TEXTURE_1a4ffb4825a0f1a88ed9d053885b8b76a2) | 
`public int `[`mode`](#struct__TEXTURE_1a8d4d85bf39f7db3c325a1671ec893c9a) | 
`public int `[`flags`](#struct__TEXTURE_1a349273ac18be5da0ddc44ed8f89caa6f) | 
`public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` * `[`asset`](#struct__TEXTURE_1ac77ecc22c4b881f44e87e6c9bf8f60bd) | 
`public `[`ASSET_PACK`](#texture_8h_1a293ce46aca895de2bc466899f2298e31)` * `[`assets`](#struct__TEXTURE_1a97afbfe433e1b550d1d378579f6856c4) | 
`public union `[`_TEXTURE`](#struct__TEXTURE)` `[``](#struct__TEXTURE_1a306bfd8362a2d23f04bc624e94dbe639) | 

## Members

#### `public GLuint `[`id`](#struct__TEXTURE_1a4ffb4825a0f1a88ed9d053885b8b76a2) 

#### `public int `[`mode`](#struct__TEXTURE_1a8d4d85bf39f7db3c325a1671ec893c9a) 

#### `public int `[`flags`](#struct__TEXTURE_1a349273ac18be5da0ddc44ed8f89caa6f) 

#### `public `[`ASSET`](#texture_8h_1a88f656c0d2846dc165c5bf595886f07d)` * `[`asset`](#struct__TEXTURE_1ac77ecc22c4b881f44e87e6c9bf8f60bd) 

#### `public `[`ASSET_PACK`](#texture_8h_1a293ce46aca895de2bc466899f2298e31)` * `[`assets`](#struct__TEXTURE_1a97afbfe433e1b550d1d378579f6856c4) 

#### `public union `[`_TEXTURE`](#struct__TEXTURE)` `[``](#struct__TEXTURE_1a306bfd8362a2d23f04bc624e94dbe639) 

# struct `_TEXTURE_PACK` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`scale`](#struct__TEXTURE__PACK_1ab026ecd9fba2a4dfea562d90a75f1944) | 
`public float `[`strength`](#struct__TEXTURE__PACK_1aab81a3e8aac8f463438d4432d1201fd3) | 
`public `[`ASSET_PACK`](#texture_8h_1a293ce46aca895de2bc466899f2298e31)` * `[`assets`](#struct__TEXTURE__PACK_1a066d93c0db74c92e60a1559a5ee33ff6) | 
`public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`index`](#struct__TEXTURE__PACK_1a6c391cd294f251f5e39103abce042ab1) | 
`public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`tex`](#struct__TEXTURE__PACK_1a28dab9e72decc3a1dbf48b6c95a27af8) | 
`public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`norm`](#struct__TEXTURE__PACK_1ab8f17530c68f65442949d260ebcd7389) | 
`public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`disp`](#struct__TEXTURE__PACK_1ade26899ddbe463a688c6d2e87b831cda) | 
`public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`occl`](#struct__TEXTURE__PACK_1a9ec473ce33bafc59a50ec806b07a17bc) | 
`public union `[`_TEXTURE_PACK`](#struct__TEXTURE__PACK)` `[``](#struct__TEXTURE__PACK_1ab94cab76209a2d9b00a40b26a4d9ac4c) | 

## Members

#### `public float `[`scale`](#struct__TEXTURE__PACK_1ab026ecd9fba2a4dfea562d90a75f1944) 

#### `public float `[`strength`](#struct__TEXTURE__PACK_1aab81a3e8aac8f463438d4432d1201fd3) 

#### `public `[`ASSET_PACK`](#texture_8h_1a293ce46aca895de2bc466899f2298e31)` * `[`assets`](#struct__TEXTURE__PACK_1a066d93c0db74c92e60a1559a5ee33ff6) 

#### `public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`index`](#struct__TEXTURE__PACK_1a6c391cd294f251f5e39103abce042ab1) 

#### `public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`tex`](#struct__TEXTURE__PACK_1a28dab9e72decc3a1dbf48b6c95a27af8) 

#### `public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`norm`](#struct__TEXTURE__PACK_1ab8f17530c68f65442949d260ebcd7389) 

#### `public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`disp`](#struct__TEXTURE__PACK_1ade26899ddbe463a688c6d2e87b831cda) 

#### `public `[`TEXTURE`](#texture_8h_1a10926c88f1426b0785798374a2a208fc)` `[`occl`](#struct__TEXTURE__PACK_1a9ec473ce33bafc59a50ec806b07a17bc) 

#### `public union `[`_TEXTURE_PACK`](#struct__TEXTURE__PACK)` `[``](#struct__TEXTURE__PACK_1ab94cab76209a2d9b00a40b26a4d9ac4c) 

# struct `BEHAVE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`pos`](#structBEHAVE_1a70e97f8d05a144857bb1162898aca729) | 
`public vec3 `[`vel`](#structBEHAVE_1a409440e4810bc753167c85aee53ccce0) | 
`public float `[`scale`](#structBEHAVE_1a331517809c356364da474b8aa36f828b) | 
`public float `[`mass`](#structBEHAVE_1a8ead0b4b93b4c96248278201f4bb32d4) | 
`public vec3 `[`impulse`](#structBEHAVE_1a59ba1266d45634e6ab41b557e724926c) | 
`public vec3 `[`deltav`](#structBEHAVE_1a99aa2bdee4435edfdca52199ceff8f4e) | 
`public vec3 `[`shift`](#structBEHAVE_1a795abeb04e1c5cd3d4a2f9c7a867b955) | 

## Members

#### `public vec3 `[`pos`](#structBEHAVE_1a70e97f8d05a144857bb1162898aca729) 

#### `public vec3 `[`vel`](#structBEHAVE_1a409440e4810bc753167c85aee53ccce0) 

#### `public float `[`scale`](#structBEHAVE_1a331517809c356364da474b8aa36f828b) 

#### `public float `[`mass`](#structBEHAVE_1a8ead0b4b93b4c96248278201f4bb32d4) 

#### `public vec3 `[`impulse`](#structBEHAVE_1a59ba1266d45634e6ab41b557e724926c) 

#### `public vec3 `[`deltav`](#structBEHAVE_1a99aa2bdee4435edfdca52199ceff8f4e) 

#### `public vec3 `[`shift`](#structBEHAVE_1a795abeb04e1c5cd3d4a2f9c7a867b955) 

# struct `BEZIER` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`point`](#structBEZIER_1a51d5e1f56375136cf7ff81d97f4b7183) | 
`public `[`MODEL`](#structMODEL)` `[`model`](#structBEZIER_1a1437b16da81ecda19db52c216f3aa210) | 
`public bool `[`linemode`](#structBEZIER_1a73ee362ba2f6d3ad2e40794f73c13002) | 
`public GLuint `[`point_vert_buff`](#structBEZIER_1a3e4b6d19b2d4392548b95e4ad70a4ad9) | 
`public vec3 `[`vel`](#structBEZIER_1aa534d6a7a3eba3e87fad99a2228a01ff) | 
`public  `[`MESH`](#structBEZIER_1a4b00c4f22bd1d8da5354d93f3559a7f2)`(`[`BEZIER_RESOLUTION`](#bezier_8h_1ac499d516aa39adfd084f9de688450cba)`)` | 

## Members

#### `public vec3 `[`point`](#structBEZIER_1a51d5e1f56375136cf7ff81d97f4b7183) 

#### `public `[`MODEL`](#structMODEL)` `[`model`](#structBEZIER_1a1437b16da81ecda19db52c216f3aa210) 

#### `public bool `[`linemode`](#structBEZIER_1a73ee362ba2f6d3ad2e40794f73c13002) 

#### `public GLuint `[`point_vert_buff`](#structBEZIER_1a3e4b6d19b2d4392548b95e4ad70a4ad9) 

#### `public vec3 `[`vel`](#structBEZIER_1aa534d6a7a3eba3e87fad99a2228a01ff) 

#### `public  `[`MESH`](#structBEZIER_1a4b00c4f22bd1d8da5354d93f3559a7f2)`(`[`BEZIER_RESOLUTION`](#bezier_8h_1ac499d516aa39adfd084f9de688450cba)`)` 

# struct `FRACTAL` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`x`](#structFRACTAL_1ab08930d0462a8791d44064241fcbf8b9) | 
`public float `[`y`](#structFRACTAL_1a1d53c0e7b1cb1d2018eb42f1fd46fb85) | 
`public float `[`zoom`](#structFRACTAL_1ae57b3d82c792294efc87c0a1c5b8a0f7) | 
`public float `[`rot`](#structFRACTAL_1ab4a5ccfdfc9c9bf23104c066dd108707) | 
`public `[`MODEL`](#structMODEL)` `[`model`](#structFRACTAL_1afce71f8e049ac454809c2b43d4c2a1aa) | 
`public  `[`MESH2`](#structFRACTAL_1aaf99cddd158f890418cdcc126a725e85)`(4)` | 

## Members

#### `public float `[`x`](#structFRACTAL_1ab08930d0462a8791d44064241fcbf8b9) 

#### `public float `[`y`](#structFRACTAL_1a1d53c0e7b1cb1d2018eb42f1fd46fb85) 

#### `public float `[`zoom`](#structFRACTAL_1ae57b3d82c792294efc87c0a1c5b8a0f7) 

#### `public float `[`rot`](#structFRACTAL_1ab4a5ccfdfc9c9bf23104c066dd108707) 

#### `public `[`MODEL`](#structMODEL)` `[`model`](#structFRACTAL_1afce71f8e049ac454809c2b43d4c2a1aa) 

#### `public  `[`MESH2`](#structFRACTAL_1aaf99cddd158f890418cdcc126a725e85)`(4)` 

# struct `LIGHTSOURCE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`type`](#structLIGHTSOURCE_1a2f8a86fe755a47f68a349be822e1b8bf) | 
`public `[`LIGHTSOURCE_DIR`](#structLIGHTSOURCE__DIR)` `[`dir`](#structLIGHTSOURCE_1aaec340c68d502020c92f7050615eece0) | 
`public `[`LIGHTSOURCE_POINT`](#structLIGHTSOURCE__POINT)` `[`point`](#structLIGHTSOURCE_1a259e576f8c65d858467839c7acdf088d) | 
`public union `[`LIGHTSOURCE`](#structLIGHTSOURCE)` `[``](#structLIGHTSOURCE_1a59816fb1c42bb0cb4f417c3b342532db) | 

## Members

#### `public int `[`type`](#structLIGHTSOURCE_1a2f8a86fe755a47f68a349be822e1b8bf) 

#### `public `[`LIGHTSOURCE_DIR`](#structLIGHTSOURCE__DIR)` `[`dir`](#structLIGHTSOURCE_1aaec340c68d502020c92f7050615eece0) 

#### `public `[`LIGHTSOURCE_POINT`](#structLIGHTSOURCE__POINT)` `[`point`](#structLIGHTSOURCE_1a259e576f8c65d858467839c7acdf088d) 

#### `public union `[`LIGHTSOURCE`](#structLIGHTSOURCE)` `[``](#structLIGHTSOURCE_1a59816fb1c42bb0cb4f417c3b342532db) 

# struct `LIGHTSOURCE_DIR` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`norm`](#structLIGHTSOURCE__DIR_1abffb78d983657478808748c04b001d32) | 
`public float `[`amb`](#structLIGHTSOURCE__DIR_1aae2ae0af7fe63de1bf319aabe1422da8) | 
`public float `[`bright`](#structLIGHTSOURCE__DIR_1a474fd74b3d70cfea87998c4b5178ea04) | 
`public `[`COLOR`](#unionCOLOR)` `[`diff_color`](#structLIGHTSOURCE__DIR_1ae8f8b04b52ea10745682bd0f86ea21a9) | 
`public `[`COLOR`](#unionCOLOR)` `[`amb_color`](#structLIGHTSOURCE__DIR_1aa43396f4fbd3c441a336b2c397a4b25b) | 

## Members

#### `public vec3 `[`norm`](#structLIGHTSOURCE__DIR_1abffb78d983657478808748c04b001d32) 

#### `public float `[`amb`](#structLIGHTSOURCE__DIR_1aae2ae0af7fe63de1bf319aabe1422da8) 

#### `public float `[`bright`](#structLIGHTSOURCE__DIR_1a474fd74b3d70cfea87998c4b5178ea04) 

#### `public `[`COLOR`](#unionCOLOR)` `[`diff_color`](#structLIGHTSOURCE__DIR_1ae8f8b04b52ea10745682bd0f86ea21a9) 

#### `public `[`COLOR`](#unionCOLOR)` `[`amb_color`](#structLIGHTSOURCE__DIR_1aa43396f4fbd3c441a336b2c397a4b25b) 

# struct `LIGHTSOURCE_POINT` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`pos`](#structLIGHTSOURCE__POINT_1a90f12fced75fda4680d83bd0b37c5888) | 
`public float `[`amb`](#structLIGHTSOURCE__POINT_1a67d18bd53b3c6611d863f5dfccb2e1f1) | 
`public float `[`bright`](#structLIGHTSOURCE__POINT_1a7f7441c2869bca7fbf8a81cbb6d53132) | 
`public `[`COLOR`](#unionCOLOR)` `[`diff_color`](#structLIGHTSOURCE__POINT_1a445a84f1a986e51d2b72d7f4f02a5610) | 
`public `[`COLOR`](#unionCOLOR)` `[`amb_color`](#structLIGHTSOURCE__POINT_1a648c5b20e5fbbb82b33e83e70c754107) | 

## Members

#### `public vec3 `[`pos`](#structLIGHTSOURCE__POINT_1a90f12fced75fda4680d83bd0b37c5888) 

#### `public float `[`amb`](#structLIGHTSOURCE__POINT_1a67d18bd53b3c6611d863f5dfccb2e1f1) 

#### `public float `[`bright`](#structLIGHTSOURCE__POINT_1a7f7441c2869bca7fbf8a81cbb6d53132) 

#### `public `[`COLOR`](#unionCOLOR)` `[`diff_color`](#structLIGHTSOURCE__POINT_1a445a84f1a986e51d2b72d7f4f02a5610) 

#### `public `[`COLOR`](#unionCOLOR)` `[`amb_color`](#structLIGHTSOURCE__POINT_1a648c5b20e5fbbb82b33e83e70c754107) 

# struct `MAZE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`mode`](#structMAZE_1a271fd94d5ce5f7484d39ac10c90f4e2e) | 
`public int `[`cols`](#structMAZE_1adf73805dce5fe631a0454fd1a1668894) | 
`public int `[`rows`](#structMAZE_1ac6f68a1553e245db68fa17f53107d3c8) | 
`public float `[`x`](#structMAZE_1a513f329d5d17bf0af8ba13b92e306892) | 
`public float `[`y`](#structMAZE_1a77330bce81377e2cb34dfeda432e6f7d) | 
`public float `[`scale`](#structMAZE_1a5fffb19bec1350e051bb1ecc699f7c59) | 
`public `[`COLOR`](#unionCOLOR)` `[`color`](#structMAZE_1a25f513271742b3380db4f46e6a329514) | 
`public `[`COLOR`](#unionCOLOR)` `[`color2`](#structMAZE_1aa94729cb511a1565f98e95a653580edc) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_2d`](#structMAZE_1a8174cd5b3931fb5f3c07b17164519814) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_3d`](#structMAZE_1a92cbe2cc0cd7a58fb0605f78e30572e5) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_detailed`](#structMAZE_1abc15c1aa91220ad302cfc438280c2992) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_trail`](#structMAZE_1a6c81a383e3d1bef74ff84d46db817d79) | 
`public void * `[`hwalls`](#structMAZE_1a3f1232ed0035f2d7255fb79c9b14939c) | 
`public void * `[`vwalls`](#structMAZE_1a3152bee2922ebe06fe106a95374e48ea) | 
`public void * `[`grid`](#structMAZE_1a6c8d2397045a7e4f1a67baedd0a7b1d1) | 
`public `[`DRAWSURFACE`](#drawsurface_8h_1aa5386d8c0dc671783e4a26eca68b09e7)` `[`surface`](#structMAZE_1ad1e2815bd42d10386db7888cd459827e) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall`](#structMAZE_1a0017902f332aa9e6cbd15a2da4b78579) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall2`](#structMAZE_1aebf06afbc1664a3f8d713c325ad93d40) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall_norm`](#structMAZE_1a87511ead43eaf45773d4b63b697cb0f8) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall_norm2`](#structMAZE_1abca2bf0616f0aed2c524d8318a1d25d1) | 
`public bool `[`hide_upper_walls`](#structMAZE_1a81ca1e3db99b1b100fb56b27d6d3a61a) | 

## Members

#### `public int `[`mode`](#structMAZE_1a271fd94d5ce5f7484d39ac10c90f4e2e) 

#### `public int `[`cols`](#structMAZE_1adf73805dce5fe631a0454fd1a1668894) 

#### `public int `[`rows`](#structMAZE_1ac6f68a1553e245db68fa17f53107d3c8) 

#### `public float `[`x`](#structMAZE_1a513f329d5d17bf0af8ba13b92e306892) 

#### `public float `[`y`](#structMAZE_1a77330bce81377e2cb34dfeda432e6f7d) 

#### `public float `[`scale`](#structMAZE_1a5fffb19bec1350e051bb1ecc699f7c59) 

#### `public `[`COLOR`](#unionCOLOR)` `[`color`](#structMAZE_1a25f513271742b3380db4f46e6a329514) 

#### `public `[`COLOR`](#unionCOLOR)` `[`color2`](#structMAZE_1aa94729cb511a1565f98e95a653580edc) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_2d`](#structMAZE_1a8174cd5b3931fb5f3c07b17164519814) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_3d`](#structMAZE_1a92cbe2cc0cd7a58fb0605f78e30572e5) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_detailed`](#structMAZE_1abc15c1aa91220ad302cfc438280c2992) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader_trail`](#structMAZE_1a6c81a383e3d1bef74ff84d46db817d79) 

#### `public void * `[`hwalls`](#structMAZE_1a3f1232ed0035f2d7255fb79c9b14939c) 

#### `public void * `[`vwalls`](#structMAZE_1a3152bee2922ebe06fe106a95374e48ea) 

#### `public void * `[`grid`](#structMAZE_1a6c8d2397045a7e4f1a67baedd0a7b1d1) 

#### `public `[`DRAWSURFACE`](#drawsurface_8h_1aa5386d8c0dc671783e4a26eca68b09e7)` `[`surface`](#structMAZE_1ad1e2815bd42d10386db7888cd459827e) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall`](#structMAZE_1a0017902f332aa9e6cbd15a2da4b78579) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall2`](#structMAZE_1aebf06afbc1664a3f8d713c325ad93d40) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall_norm`](#structMAZE_1a87511ead43eaf45773d4b63b697cb0f8) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture_wall_norm2`](#structMAZE_1abca2bf0616f0aed2c524d8318a1d25d1) 

#### `public bool `[`hide_upper_walls`](#structMAZE_1a81ca1e3db99b1b100fb56b27d6d3a61a) 

# struct `MAZE_WALLS` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned char * `[`up`](#structMAZE__WALLS_1a4ebaaeffd5d4737739ea22bfc4f1d84c) | 
`public unsigned char * `[`down`](#structMAZE__WALLS_1a743a0c9796567d297455de01f1483bf7) | 
`public unsigned char * `[`left`](#structMAZE__WALLS_1ac453d8d2ede3e5ad95eb023a79bee921) | 
`public unsigned char * `[`right`](#structMAZE__WALLS_1a85baba69bba49fd3b2d7d388aaa85051) | 

## Members

#### `public unsigned char * `[`up`](#structMAZE__WALLS_1a4ebaaeffd5d4737739ea22bfc4f1d84c) 

#### `public unsigned char * `[`down`](#structMAZE__WALLS_1a743a0c9796567d297455de01f1483bf7) 

#### `public unsigned char * `[`left`](#structMAZE__WALLS_1ac453d8d2ede3e5ad95eb023a79bee921) 

#### `public unsigned char * `[`right`](#structMAZE__WALLS_1a85baba69bba49fd3b2d7d388aaa85051) 

# struct `MODEL` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`COLOR`](#unionCOLOR)` `[`color`](#structMODEL_1ab9aebf27f024967f313e9954a125fb45) | 
`public `[`MESH`](#model_8h_1a9bb303cf086b8a5bd258f6a761f3fc4c)` * `[`mesh`](#structMODEL_1ac1f6c2888c95d9bc05a8734ac2fef6b5) | 
`public int `[`id`](#structMODEL_1a4dabe68ce2d1dec87a19889f1fc02dc5) | 
`public void * `[`data`](#structMODEL_1a3d5c5bbbd13349d8818c0fa00d4e010f) | 
`public bool `[`visable`](#structMODEL_1a4acf9cb6900a0e76e4109e4a7073bc37) | 
`public GLenum `[`gl_usage`](#structMODEL_1a54c233e42f0db5f213a99e917302d476) | 
`public `[`UPDATE_CALLBACK`](#model_8h_1a2a6f024f2b61423ba0e0d0c236860439)` `[`update_call`](#structMODEL_1a712d2ab04d411b583910e4714b723963) | 
`public `[`DRAW_CALLBACK`](#model_8h_1af9654667df662251d30143ba4500fbaa)` `[`draw_call`](#structMODEL_1aa2ba90df9bbd4ec5beddee4cb230c965) | 
`public mat4 `[`view_mat`](#structMODEL_1a9d5f7c7c5979829589ea0dbc7ac77979) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture`](#structMODEL_1ae90b171d733b77f575a7eacc2cde7e95) | 
`public GLuint `[`vert_buff`](#structMODEL_1a071282467cf3eca14298ecabdd72b922) | 

## Members

#### `public `[`COLOR`](#unionCOLOR)` `[`color`](#structMODEL_1ab9aebf27f024967f313e9954a125fb45) 

#### `public `[`MESH`](#model_8h_1a9bb303cf086b8a5bd258f6a761f3fc4c)` * `[`mesh`](#structMODEL_1ac1f6c2888c95d9bc05a8734ac2fef6b5) 

#### `public int `[`id`](#structMODEL_1a4dabe68ce2d1dec87a19889f1fc02dc5) 

#### `public void * `[`data`](#structMODEL_1a3d5c5bbbd13349d8818c0fa00d4e010f) 

#### `public bool `[`visable`](#structMODEL_1a4acf9cb6900a0e76e4109e4a7073bc37) 

#### `public GLenum `[`gl_usage`](#structMODEL_1a54c233e42f0db5f213a99e917302d476) 

#### `public `[`UPDATE_CALLBACK`](#model_8h_1a2a6f024f2b61423ba0e0d0c236860439)` `[`update_call`](#structMODEL_1a712d2ab04d411b583910e4714b723963) 

#### `public `[`DRAW_CALLBACK`](#model_8h_1af9654667df662251d30143ba4500fbaa)` `[`draw_call`](#structMODEL_1aa2ba90df9bbd4ec5beddee4cb230c965) 

#### `public mat4 `[`view_mat`](#structMODEL_1a9d5f7c7c5979829589ea0dbc7ac77979) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture`](#structMODEL_1ae90b171d733b77f575a7eacc2cde7e95) 

#### `public GLuint `[`vert_buff`](#structMODEL_1a071282467cf3eca14298ecabdd72b922) 

# struct `MOUSE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`x`](#structMOUSE_1ace5d337c6fc34e0e2449c43b4577ef1e) | 
`public int `[`y`](#structMOUSE_1adb4325b3aea1cf944d3f53a55c4633b9) | 
`public int `[`dx`](#structMOUSE_1aaf460a8e882a66ab2689fbd5a67572ff) | 
`public int `[`dy`](#structMOUSE_1a74444ee155e41abc543ea1e4dca9a5fb) | 
`public bool `[`grabbed`](#structMOUSE_1a4d66ba83d2c3f312b91658bf84ca08fe) | 
`public bool `[`grabby`](#structMOUSE_1af669d7a2f2a5c0f02ead70563b631059) | 
`public bool `[`first_interaction`](#structMOUSE_1a45b15b063cba06d61b1cd57a4d86f84c) | 
`public char `[`button`](#structMOUSE_1a6d977db12d57d9841f479c59a05b7284) | 

## Members

#### `public int `[`x`](#structMOUSE_1ace5d337c6fc34e0e2449c43b4577ef1e) 

#### `public int `[`y`](#structMOUSE_1adb4325b3aea1cf944d3f53a55c4633b9) 

#### `public int `[`dx`](#structMOUSE_1aaf460a8e882a66ab2689fbd5a67572ff) 

#### `public int `[`dy`](#structMOUSE_1a74444ee155e41abc543ea1e4dca9a5fb) 

#### `public bool `[`grabbed`](#structMOUSE_1a4d66ba83d2c3f312b91658bf84ca08fe) 

#### `public bool `[`grabby`](#structMOUSE_1af669d7a2f2a5c0f02ead70563b631059) 

#### `public bool `[`first_interaction`](#structMOUSE_1a45b15b063cba06d61b1cd57a4d86f84c) 

#### `public char `[`button`](#structMOUSE_1a6d977db12d57d9841f479c59a05b7284) 

# struct `PMOUSE` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`mode`](#structPMOUSE_1afdfcf488f648038f66a1056cad0d27c6) | 
`public float `[`_x`](#structPMOUSE_1a76959c338a87133d43ec621ac7c173a9) | 
`public float `[`_y`](#structPMOUSE_1affbdb18751da668439b3902538928925) | 
`public float `[`x`](#structPMOUSE_1a28671bba73e88b63fc272d83d3327b16) | 
`public float `[`y`](#structPMOUSE_1abea5e134b315f74b837bfb5e9006d257) | 
`public float `[`px`](#structPMOUSE_1ac95b98d208ea666ae617b72fb570d4db) | 
`public float `[`py`](#structPMOUSE_1aa30ba8594d92681475d77b8fb0164372) | 
`public float `[`dx`](#structPMOUSE_1ace393d0b001766ed51c5ede310918ad6) | 
`public float `[`dy`](#structPMOUSE_1afa224979dc9e85cc41740e4a8a6c279b) | 
`public vec3 `[`wave`](#structPMOUSE_1a4cdd3f85245fcd2be376e795121d9c6e) | 
`public vec3 `[`wave2`](#structPMOUSE_1a4cd96a895641b31db6612cc56930c63a) | 
`public bool `[`is_moving`](#structPMOUSE_1ab34378b0f60e2c7faec108aa33fe0d36) | 
`public float `[`sample`](#structPMOUSE_1a45e6f5b4bcb7152cecc3251d2f7d1db7) | 
`public float `[`scale`](#structPMOUSE_1a56fbcb3d99e654717164cbf737370228) | 
`public float `[`speed`](#structPMOUSE_1a15f4a13a316aaa4b5ddb7d3392e75dd1) | 
`public `[`COLOR`](#unionCOLOR)` `[`color`](#structPMOUSE_1ae6220de48f0713734cb990d8fe0700a0) | 
`public `[`COLOR`](#unionCOLOR)` `[`pcolor`](#structPMOUSE_1a54d4991bde6a42039da83fb53b610e03) | 
`public `[`MAZE`](#structMAZE)` * `[`maze`](#structPMOUSE_1af695b9953dbfcab93f1dc5bbb91182b2) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader2`](#structPMOUSE_1a6eeed9ccffbc708eaaaeb23d73f094f9) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader3`](#structPMOUSE_1af5384ebdf5368fc8a35033d370b9311d) | 
`public `[`CAMERA`](#camera_8h_1abc3f2684800c7c4d76f15cbf26fd2e9e)` `[`trail_camera`](#structPMOUSE_1af393349d08f49ac315db8b0ce3fd1268) | 
`public `[`CAMERA`](#camera_8h_1abc3f2684800c7c4d76f15cbf26fd2e9e)` `[`camera`](#structPMOUSE_1a20e80919810c480ff03bf30a3b9fcadc) | 
`public vec3 `[`_cpos`](#structPMOUSE_1aa3151b15d5127f1a1f498991b90caa8c) | 

## Members

#### `public int `[`mode`](#structPMOUSE_1afdfcf488f648038f66a1056cad0d27c6) 

#### `public float `[`_x`](#structPMOUSE_1a76959c338a87133d43ec621ac7c173a9) 

#### `public float `[`_y`](#structPMOUSE_1affbdb18751da668439b3902538928925) 

#### `public float `[`x`](#structPMOUSE_1a28671bba73e88b63fc272d83d3327b16) 

#### `public float `[`y`](#structPMOUSE_1abea5e134b315f74b837bfb5e9006d257) 

#### `public float `[`px`](#structPMOUSE_1ac95b98d208ea666ae617b72fb570d4db) 

#### `public float `[`py`](#structPMOUSE_1aa30ba8594d92681475d77b8fb0164372) 

#### `public float `[`dx`](#structPMOUSE_1ace393d0b001766ed51c5ede310918ad6) 

#### `public float `[`dy`](#structPMOUSE_1afa224979dc9e85cc41740e4a8a6c279b) 

#### `public vec3 `[`wave`](#structPMOUSE_1a4cdd3f85245fcd2be376e795121d9c6e) 

#### `public vec3 `[`wave2`](#structPMOUSE_1a4cd96a895641b31db6612cc56930c63a) 

#### `public bool `[`is_moving`](#structPMOUSE_1ab34378b0f60e2c7faec108aa33fe0d36) 

#### `public float `[`sample`](#structPMOUSE_1a45e6f5b4bcb7152cecc3251d2f7d1db7) 

#### `public float `[`scale`](#structPMOUSE_1a56fbcb3d99e654717164cbf737370228) 

#### `public float `[`speed`](#structPMOUSE_1a15f4a13a316aaa4b5ddb7d3392e75dd1) 

#### `public `[`COLOR`](#unionCOLOR)` `[`color`](#structPMOUSE_1ae6220de48f0713734cb990d8fe0700a0) 

#### `public `[`COLOR`](#unionCOLOR)` `[`pcolor`](#structPMOUSE_1a54d4991bde6a42039da83fb53b610e03) 

#### `public `[`MAZE`](#structMAZE)` * `[`maze`](#structPMOUSE_1af695b9953dbfcab93f1dc5bbb91182b2) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader2`](#structPMOUSE_1a6eeed9ccffbc708eaaaeb23d73f094f9) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader3`](#structPMOUSE_1af5384ebdf5368fc8a35033d370b9311d) 

#### `public `[`CAMERA`](#camera_8h_1abc3f2684800c7c4d76f15cbf26fd2e9e)` `[`trail_camera`](#structPMOUSE_1af393349d08f49ac315db8b0ce3fd1268) 

#### `public `[`CAMERA`](#camera_8h_1abc3f2684800c7c4d76f15cbf26fd2e9e)` `[`camera`](#structPMOUSE_1a20e80919810c480ff03bf30a3b9fcadc) 

#### `public vec3 `[`_cpos`](#structPMOUSE_1aa3151b15d5127f1a1f498991b90caa8c) 

# struct `SHADER_DESCRIPTOR` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`active`](#structSHADER__DESCRIPTOR_1a3d631181a105b1dfc2f39c37922806fe) | 
`public unsigned int * `[`program`](#structSHADER__DESCRIPTOR_1a3d72db4645db4a4e5629ad3832c71434) | 
`public char * `[`program_name`](#structSHADER__DESCRIPTOR_1adfaadf7f3e4943c90b7e68721a086dca) | 
`public char * `[`vert_name`](#structSHADER__DESCRIPTOR_1a7ade841d164a3ebf08663f90839fd05b) | 
`public char * `[`vert_src`](#structSHADER__DESCRIPTOR_1a6bb4fac362317642bf339d32c2190bab) | 
`public char * `[`frag_name`](#structSHADER__DESCRIPTOR_1a0d5631d4090697fe7803dfc452c46fa2) | 
`public char * `[`frag_src`](#structSHADER__DESCRIPTOR_1aa8a9d3a32b1c34c5f19e736babd1622b) | 

## Members

#### `public bool `[`active`](#structSHADER__DESCRIPTOR_1a3d631181a105b1dfc2f39c37922806fe) 

#### `public unsigned int * `[`program`](#structSHADER__DESCRIPTOR_1a3d72db4645db4a4e5629ad3832c71434) 

#### `public char * `[`program_name`](#structSHADER__DESCRIPTOR_1adfaadf7f3e4943c90b7e68721a086dca) 

#### `public char * `[`vert_name`](#structSHADER__DESCRIPTOR_1a7ade841d164a3ebf08663f90839fd05b) 

#### `public char * `[`vert_src`](#structSHADER__DESCRIPTOR_1a6bb4fac362317642bf339d32c2190bab) 

#### `public char * `[`frag_name`](#structSHADER__DESCRIPTOR_1a0d5631d4090697fe7803dfc452c46fa2) 

#### `public char * `[`frag_src`](#structSHADER__DESCRIPTOR_1aa8a9d3a32b1c34c5f19e736babd1622b) 

# struct `TERRAIN` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`pos`](#structTERRAIN_1acea9538483c47af9b0360f14bef110c9) | 
`public vec3 `[`scale`](#structTERRAIN_1a11ea20499ad4b26e2c64e12d745099d8) | 
`public `[`COLOR`](#unionCOLOR)` `[`color`](#structTERRAIN_1aa6c36e835f89b08ee26be0950a02cdeb) | 
`public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture`](#structTERRAIN_1a606e1501c1baa39a019b727a42b41747) | 
`public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader`](#structTERRAIN_1a2887a69aa0b658535701e96db2972882) | 
`public `[`MODEL`](#structMODEL)` `[`model`](#structTERRAIN_1a16c9bf72cef7126177077d9c2fe7a867) | 
`public `[`MESH`](#model_8h_1a9bb303cf086b8a5bd258f6a761f3fc4c)` * `[`mesh`](#structTERRAIN_1ab5bb710b188986afc38c55ff7bc09cb8) | 
`public `[`GEN_MODEL`](#terrain_8h_1a3f9a360191af6ecb9d9554db241837d5)` * `[`gen_model`](#structTERRAIN_1ad67f67e8d19c744106b6fdcb4f736d04) | 

## Members

#### `public vec3 `[`pos`](#structTERRAIN_1acea9538483c47af9b0360f14bef110c9) 

#### `public vec3 `[`scale`](#structTERRAIN_1a11ea20499ad4b26e2c64e12d745099d8) 

#### `public `[`COLOR`](#unionCOLOR)` `[`color`](#structTERRAIN_1aa6c36e835f89b08ee26be0950a02cdeb) 

#### `public `[`TEXTURE`](#model_8h_1a10926c88f1426b0785798374a2a208fc)` * `[`texture`](#structTERRAIN_1a606e1501c1baa39a019b727a42b41747) 

#### `public `[`SHADER`](#model_8h_1a557da19759c60ec849641df0ceed2c6d)` * `[`shader`](#structTERRAIN_1a2887a69aa0b658535701e96db2972882) 

#### `public `[`MODEL`](#structMODEL)` `[`model`](#structTERRAIN_1a16c9bf72cef7126177077d9c2fe7a867) 

#### `public `[`MESH`](#model_8h_1a9bb303cf086b8a5bd258f6a761f3fc4c)` * `[`mesh`](#structTERRAIN_1ab5bb710b188986afc38c55ff7bc09cb8) 

#### `public `[`GEN_MODEL`](#terrain_8h_1a3f9a360191af6ecb9d9554db241837d5)` * `[`gen_model`](#structTERRAIN_1ad67f67e8d19c744106b6fdcb4f736d04) 

# struct `vec3_pack` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public vec3 `[`pack`](#structvec3__pack_1ac95f232d6c536f317d1a04ccfe610c44) | 
`public vec3 `[`unpack`](#structvec3__pack_1adb56b5f144b7ff81db7f4dc77c4fdc55) | 
`public union `[`vec3_pack`](#structvec3__pack)` `[``](#structvec3__pack_1aea8807a8dbccaf7c7fc576acd5d5effb) | 

## Members

#### `public vec3 `[`pack`](#structvec3__pack_1ac95f232d6c536f317d1a04ccfe610c44) 

#### `public vec3 `[`unpack`](#structvec3__pack_1adb56b5f144b7ff81db7f4dc77c4fdc55) 

#### `public union `[`vec3_pack`](#structvec3__pack)` `[``](#structvec3__pack_1aea8807a8dbccaf7c7fc576acd5d5effb) 

# struct `WORLD` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`LIGHTSOURCE`](#structLIGHTSOURCE)` `[`light`](#structWORLD_1abb25ba53fb13ae5f0bebf91d6f2fa608) | 

## Members

#### `public `[`LIGHTSOURCE`](#structLIGHTSOURCE)` `[`light`](#structWORLD_1abb25ba53fb13ae5f0bebf91d6f2fa608) 

Generated by [Moxygen](https://sourcey.com/moxygen)