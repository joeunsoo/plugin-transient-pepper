export default function Component() {
  return (
    <>
      <defs>

        <filter id="dropshadow" width="180%" height="180%">
          <feGaussianBlur in="SourceAlpha" stdDeviation="6" result="blurredAlpha" />
          <feOffset in="blurredAlpha" dx="0" dy="25" result="offsetShadow" />
          <feFlood floodColor="#000" floodOpacity="0.9" result="shadowColor" />
          <feComposite in="shadowColor" in2="offsetShadow" operator="in" result="coloredShadow" />
          <feMerge>
            <feMergeNode in="coloredShadow" />
            <feMergeNode in="SourceGraphic" />
          </feMerge>
        </filter>

        <filter id="whiteGlow">
          <feGaussianBlur in="SourceGraphic" stdDeviation="10" result="blur" />
          <feSpecularLighting
            in="color" surfaceScale="2" specularConstant="2"
            specularExponent="30" lightingColor="var(--mui-palette-common-white)"
            result="specular"
          >
            <feDistantLight azimuth="225" elevation="10" />
          </feSpecularLighting>
          <feComposite
            in="specular" in2="SourceGraphic" operator="arithmetic"
            k1="0" k2="2" k3="1.0" k4="0"
          />
        </filter>

        <filter id="redGlow">
          <feGaussianBlur in="SourceGraphic" stdDeviation="10" result="blur" />
          <feSpecularLighting
            in="color" surfaceScale="2" specularConstant="2"
            specularExponent="30" lightingColor="var(--mui-palette-secondary-main)"
            result="specular"
          >
            <feDistantLight azimuth="45" elevation="10" />
          </feSpecularLighting>
          <feComposite
            in="specular" in2="SourceGraphic" operator="arithmetic"
            k1="0" k2="1" k3="1" k4="0"
          />
        </filter>
      </defs>
      <g transform="translate(100,100)">
        <g filter="url(#whiteGlow)">
          <g filter="url(#redGlow)">
            <circle
              r={65}
              fill="var(--mui-palette-primary-dark)"
            />
          </g>
        </g>

        <linearGradient id="rimHL" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0%" stopColor="#000000" stopOpacity="0.4" />
          <stop offset="40%" stopColor="#000000" stopOpacity="0.6" />
          <stop offset="60%" stopColor="#000000" stopOpacity="1.0" />
          <stop offset="100%" stopColor="#000000" stopOpacity="0" />
        </linearGradient>
        <circle r="68" fill="none" stroke="#000000" strokeWidth="10" opacity="0.2" />
        <circle r="68" fill="none" stroke="url(#rimHL)" strokeWidth="10" opacity="0.3" />
        <circle r="65" fill="none" stroke="#000000" strokeWidth="1" />
        <circle r="59" fill="none" stroke="url(#rimHL)" strokeWidth="11" opacity="1.0" />

        <linearGradient id="mainGradient" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="black" stopOpacity="0" />
          <stop offset="100%" stopColor="black" stopOpacity="0.3" />
        </linearGradient>

        <g filter="url(#dropshadow)">
          <g filter="url(#whiteGlow)">
            <g filter="url(#redGlow)">
              <circle
                r={50}
                fill="var(--mui-palette-primary-darker)"
              />
            </g>
          </g>
        </g>
        <circle r={50} fill="url(#mainGradient)" />

        <linearGradient id="stroke" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="var(--mui-palette-common-white)" stopOpacity="1.0" />
          <stop offset="20%" stopColor="var(--mui-palette-primary-main)" stopOpacity="0" />
          <stop offset="80%" stopColor="var(--mui-palette-primary-main)" stopOpacity="0" />
          <stop offset="100%" stopColor="var(--mui-palette-secondary-main)" stopOpacity="1.0" />
        </linearGradient>
        <g transform="rotate(-35)">
          <circle r={52} fill="none" stroke="var(--mui-palette-primary-main)" strokeWidth="2" />
          <circle r={52} fill="none" stroke="url(#stroke)" strokeWidth="2" />
          <circle r={54} fill="none" stroke="#000000" strokeWidth="2" />
        </g>

        <radialGradient id="ring" cx="50%" cy="50%" r="50%">
          <stop offset="0%" stopColor="#000000" stopOpacity="0.0" />
          <stop offset="80%" stopColor="#000000" stopOpacity="1.0" />
        </radialGradient>
        <circle r={55} fill="url(#ring)" opacity="0.3" />

        <linearGradient id="rimCover" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0%" stopColor="#000000" stopOpacity="0.4" />
          <stop offset="40%" stopColor="#000000" stopOpacity="0.6" />
          <stop offset="60%" stopColor="#000000" stopOpacity="1.0" />
          <stop offset="100%" stopColor="#000000" stopOpacity="0.5" />
        </linearGradient>
        <circle r={60} fill="none" stroke="url(#rimCover)" strokeWidth={10} opacity="0.3" />

      </g>
    </>
  );
}
