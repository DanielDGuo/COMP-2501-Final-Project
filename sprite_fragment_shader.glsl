// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

// Texture sampler
uniform sampler2D onetex;
uniform int deceased;
uniform int TileNum;

void main()
{
    // Sample texture
    vec4 color = texture2D(onetex, uv_interp * TileNum);

    // Assign color to fragment

    if(deceased == 1){
        //find the average to greyscale by
        float greyScale = (color.r + color.g + color.b)/3;
        gl_FragColor = vec4(greyScale, greyScale, greyScale, color.a);    
    }else{
        gl_FragColor = vec4(color.r, color.g, color.b, color.a);
    }


    // Check for transparency
    if(color.a < 1.0)
    {
         discard;
    }
}
