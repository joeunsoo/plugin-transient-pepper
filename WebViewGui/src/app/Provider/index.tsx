import MuiProvider from './MuiProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import SnackbarProvider from './SnackbarProvider';
import PeakMeter from '@/src/ui/Meter/PeakMeter';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
    <MuiProvider>
      {children}
      <AboutProvider />
      <PeakMeter />
      <AnalysisDataProvider />
      <SnackbarProvider />
    </MuiProvider>
  );
}
