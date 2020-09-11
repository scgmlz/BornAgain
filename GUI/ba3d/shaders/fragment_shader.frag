uniform highp vec3 lightPos1;
uniform highp vec4 color;
uniform highp float ambient;
uniform highp vec3 eye;
uniform highp bool axis;

varying highp vec3 vo, nm, ac;

void main() {
    if (axis)
    {
        // for drawing colored 3D axes
        gl_FragColor = vec4(ac, 1.0);
    }
    else
    {
        // for drawing 3D objects

        // ambient
        highp vec3 amb_col = ambient * color.rgb;

        // diffuse
        highp vec3  L1  = normalize(lightPos1 - vo);
        highp vec3  N  = normalize(nm);
        highp float NL_sum = dot(N,L1);
        highp float NL = 0.6*max(0.0, NL_sum);
        highp vec3 diff_col = NL * color.rgb;

        // specular
        float spec = 0.0;
        highp vec3 E = normalize(eye-vo);
        highp float ELN1 = pow(max(0.0, dot(E, reflect(-L1, N))), 20.0);
        if(NL > 0.0)
            spec = ELN1;
        vec3 spec_col = spec * vec3(1.0, 1.0, 1.0);

        highp vec3 tot_col = amb_col + diff_col + spec_col;
        highp vec4 C = vec4(tot_col, color.a);
        gl_FragColor = clamp(C, 0.0, 1.0);
    }
}
