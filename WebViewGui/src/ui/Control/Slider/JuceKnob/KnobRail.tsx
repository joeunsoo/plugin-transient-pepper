export default function Component() {
  return (
    <>
      <defs>
        <filter id="dropshadow" width="180%" height="180%">
          <feGaussianBlur in="SourceAlpha" stdDeviation="5" result="blurredAlpha" />
          <feOffset in="blurredAlpha" dx="0" dy="15" result="offsetShadow" />
          <feFlood floodColor="#000" floodOpacity="0.8" result="shadowColor" />
          <feComposite in="shadowColor" in2="offsetShadow" operator="in" result="coloredShadow" />
          <feMerge>
            <feMergeNode in="coloredShadow" />
            <feMergeNode in="SourceGraphic" />
          </feMerge>
        </filter>

        <filter id="innerglow">
          <feFlood floodColor="#ffffff" floodOpacity="0.3" result="flood" />
          <feComposite in="flood" in2="SourceAlpha" operator="out" result="composite1" />
          <feOffset dx="0" dy="1" in="composite1" result="offset" />
          <feGaussianBlur stdDeviation="0" in="offset" edgeMode="none" result="blur" />
          <feComposite in="blur" in2="SourceAlpha" operator="in" result="composite2" />
          <feMerge result="merge">
            <feMergeNode in="SourceGraphic" />
            <feMergeNode in="composite2" />
          </feMerge>
        </filter>

        <linearGradient id="Gradient1" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="black" stopOpacity="0" />
          <stop offset="100%" stopColor="black" stopOpacity="0.3" />
        </linearGradient>

      </defs>

      <circle
        cx={100}
        cy={100}
        r={75}
        fill="var(--mui-palette-primary-dark)"
      />

      <circle
        cx={100}
        cy={100}
        r={75}
        fill="url(#Gradient1)"
      />

      <g>
        <circle
          cx={100}
          cy={100}
          r={65}
          fill="var(--mui-palette-primary-darker)"
        />
      </g>

      <g filter="url(#dropshadow)">
        <circle
          cx={100}
          cy={100}
          r={60}
          fill="var(--mui-palette-primary-main)"
          filter="url(#innerglow)"
        />
      </g>

      <circle
        cx={100}
        cy={100}
        r={62}
        fill="url(#Gradient1)"
      />

    </>
  );
}
