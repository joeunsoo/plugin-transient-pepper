import Stack, { type StackProps } from '@mui/material/Stack';
import Led from './Led';
import { uesControlStore } from '@/store/ControlStore';
import { calcBypassWetOpacity } from '@/define';
import applySkew from '@/utils/ApplySkew';

interface PageProps extends StackProps {
  idx: number,
  length?: number,
  ignoreBypass?: boolean,
  ignoreWetSolo?: boolean,
}

export default function Page({
  idx,
  length = 15,
  sx,
  ignoreBypass = false,
  ignoreWetSolo = true,
  ...props
}: PageProps) {
  const { bypassed, wetSolo } = uesControlStore();
  const thresholds = Array.from(
    { length },
    // (v, i) => 1 - ((1 / length) * (i + 1))
    (v, i) => applySkew(1 - ((1 / length) * (i + 1)), 0.0, 1.0, 0.85)
  );

  return (
    <Stack
      spacing={0.7}
      sx={{
        height: '100%',
        flexGrow: 1,
        opacity: calcBypassWetOpacity({ bypassed, wetSolo, ignoreBypass, ignoreWetSolo }),
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
