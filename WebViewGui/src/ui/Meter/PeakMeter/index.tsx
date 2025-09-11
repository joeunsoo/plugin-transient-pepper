import Stack, { type StackProps } from '@mui/material/Stack';
import Led from './Led';
import { uesControlStore } from '@/store/ControlStore';
import { ignoreBypassOpacity } from '@/define';

interface PageProps extends StackProps {
  idx: number,
  length?: number
  ignoreBypass: boolean;
}

export default function Page({
  idx,
  length = 15,
  sx,
  ignoreBypass = false,
  ...props
}: PageProps) {
  const { bypassed } = uesControlStore();
  const thresholds = Array.from(
    { length },
    (v, i) => (1 - ((1 / length) * (i + 1)))
  );

  return (
    <Stack
      spacing={0.7}
      sx={{
        height: '100%',
        flexGrow: 1,
        opacity: (!ignoreBypass && bypassed) ? ignoreBypassOpacity : 1.0,
        ...sx
      }}
      {...props}
    >
      {thresholds.map((value, index) => (
        <Led
          key={index}
          idx={idx}
          startLevel={value}
          endLevel={thresholds[index - 1] || 1}
          mix={index / length}
        />
      ))}
    </Stack>
  );
}
