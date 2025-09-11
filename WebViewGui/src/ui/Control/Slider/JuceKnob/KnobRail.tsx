import { palette } from '@/define';

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
        <circle
          r={65}
          fill={`var(--mui-palette-${ringColor}-darken)`}
        />

        <linearGradient id="rimHL" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0%" stopColor="#000000" stopOpacity="0.4" />
          <stop offset="40%" stopColor="#000000" stopOpacity="0.6" />
          <stop offset="60%" stopColor="#000000" stopOpacity="1.0" />
          <stop offset="100%" stopColor="#000000" stopOpacity="0" />
        </linearGradient>
        <circle r="64" fill="none" stroke="#000000" strokeWidth="1" />
        <circle r="59" fill="none" stroke="url(#rimHL)" strokeWidth="11" opacity="0.5" />

        <g filter="url(#dropshadow)">
          <circle
            r={50}
            fill={`var(--mui-palette-${color}-main)`}
          />
        </g>

        <linearGradient id="lightGradient" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor={'var(--mui-palette-common-black)'} stopOpacity="0.0" />
          <stop offset="50%" stopColor={'var(--mui-palette-common-gray)'} stopOpacity="0.2" />
          <stop offset="100%" stopColor={'var(--mui-palette-common-black)'} stopOpacity="0.0" />
        </linearGradient>
        <g transform="rotate(45)">
          <circle r={50} fill="url(#lightGradient)" />
        </g>

        <linearGradient id="stroke" x1="0" x2="0" y1="0" y2="1">
          <stop offset="0%" stopColor="var(--mui-palette-common-white)" stopOpacity="1.0" />
          <stop offset="20%" stopColor="var(--mui-palette-primary-main)" stopOpacity="0" />
          <stop offset="80%" stopColor="var(--mui-palette-primary-main)" stopOpacity="0" />
          <stop offset="90%" stopColor={palette[ringColor].darkish} stopOpacity="1.0" />
        </linearGradient>
        <g transform="rotate(-35)">
          <circle r={50} fill="none" stroke={`var(--mui-palette-${color}-darker)`} strokeWidth="2" />
          <circle r={50} fill="none" stroke="url(#stroke)" strokeWidth="2" />
          <circle r={53} fill="none" stroke="#000000" strokeWidth="3" />
        </g>
      </g>
    </>
  );
}
