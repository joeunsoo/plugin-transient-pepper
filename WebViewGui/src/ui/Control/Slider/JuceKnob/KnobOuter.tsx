function Dot({
  ...props
}:React.SVGProps<SVGCircleElement>) {

  return (
      <circle
        r={4}
        fill="var(--mui-palette-primary-main)"
        {...props}
      />
  );
}

export default function Component() {
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
        stroke="var(--mui-palette-primary-darkermost)"
        strokeWidth="4"
        style={{}}
      />
      <Dot
        cx={-dotDistance}
        cy={0}
      />
      <Dot
        cx={dotX}
        cy={dotY}
      />
    </g>
  );
}
