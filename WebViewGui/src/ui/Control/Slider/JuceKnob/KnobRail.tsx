type PageProps = {
  color?: string
  ringColor?: string
}

export default function Page({
  color = 'primary',
  ringColor = 'secondary'
}: PageProps) {
  return (
    <>
      <defs>
        <filter id="dropshadow" x="-50%" y="-50%" width="200%" height="200%" filterUnits="userSpaceOnUse">
          <feGaussianBlur in="SourceAlpha" stdDeviation="6" result="blurredAlpha" />
          <feOffset in="blurredAlpha" dx="0" dy="25" result="offsetShadow" />
          <feFlood floodColor="#000" floodOpacity="0.9" result="shadowColor" />
          <feComposite in="shadowColor" in2="offsetShadow" operator="in" result="coloredShadow" />
          <feMerge>
            <feMergeNode in="coloredShadow" />
            <feMergeNode in="SourceGraphic" />
          </feMerge>
        </filter>
      </defs>
      <g transform="translate(100,100)">
        <circle r={65}
          fill={`var(--mui-palette-${ringColor}-darker)`}
          stroke="#000000"
          strokeWidth="1"
        />

        <g filter="url(#dropshadow)">
          <circle r={50} fill={`var(--mui-palette-${color}-main)`} />
        </g>

        <linearGradient id="lightGradient" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor={'var(--mantine-color-black)'} stopOpacity="0.0" />
          <stop offset="50%" stopColor={'var(--mantine-color-gray-6)'} stopOpacity="0.2" />
          <stop offset="100%" stopColor={'var(--mantine-color-black)'} stopOpacity="0.0" />
        </linearGradient>
        <g transform="rotate(45)">
          <circle
            r={50}
            fill="url(#lightGradient)"
            stroke={`var(--mui-palette-${color}-darker)`}
            strokeWidth="2"
          />
        </g>

        <linearGradient id="stroke" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="var(--mantine-color-white)" stopOpacity="1.0" />
          <stop offset="20%" stopColor="var(--mui-palette-primary-main)" stopOpacity="0" />
        </linearGradient>
        <g transform="rotate(-35)">
          <circle r={50} fill="none" stroke="url(#stroke)" strokeWidth="2" />
          <circle r={52} fill="none" stroke="#000000" strokeWidth="3" />
        </g>
      </g>
    </>
  );
}
