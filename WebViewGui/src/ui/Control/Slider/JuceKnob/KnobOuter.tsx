interface DotProps extends React.SVGProps<SVGCircleElement> {
  ringColor?: string
}

function Dot({
  ringColor= 'secondary',
  ...props
}: DotProps) {
  return (
    <circle
      r={4}
      fill={`var(--mui-palette-${ringColor}-lighten)`}
      {...props}
    />
  );
}

type PageProps = {
  ringColor?: string
}

export default function PageProps({
  ringColor = 'secondary'
}: PageProps) {
  const distance = 75;
  const dotDistance = 76;

  const angle1 = (1 * 270) - 180;
  const radian1 = angle1 * Math.PI / 180;
  const x1 = distance * Math.cos(radian1);
  const y1 = distance * Math.sin(radian1);

  const dotX = dotDistance * Math.cos(radian1);
  const dotY = dotDistance * Math.sin(radian1);

  return (
    <g
      transform="
        translate(100 100)
        rotate(-45)
      "
    >
      <path
        d={`
          M ${-distance} 0
          A ${distance} ${distance} 0 ${angle1 < 0 ? 0 : 1} 1 ${x1} ${y1}
        `}
        fill="none"
        stroke={`var(--mui-palette-${ringColor}-lighten)`}
        strokeWidth="1"
        style={{}}
      />
      <Dot
        cx={-dotDistance}
        cy={0}
        ringColor={ringColor}
      />
      <Dot
        cx={dotX}
        cy={dotY}
        ringColor={ringColor}
      />
    </g>
  );
}
