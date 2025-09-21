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
          fill={`var(--mantine-color-${ringColor}Dark-6)`}
          stroke="#000000"
          strokeWidth="1"
        />

        <g filter="url(#dropshadow)">
          <circle r={50} fill={`var(--mantine-color-${color}-6)`} />
        </g>

        <linearGradient id="stroke" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="var(--mantine-color-white)" stopOpacity="1.0" />
          <stop offset="20%" stopColor="var(--mantine-color-primary-6)" stopOpacity="0" />
        </linearGradient>
        <g transform="rotate(-35)">
          <circle r={50} fill="none" stroke="url(#stroke)" strokeWidth="2" />
          <circle r={52} fill="none" stroke="#000000" strokeWidth="3" />
        </g>
      </g>
    </>
  );
}
