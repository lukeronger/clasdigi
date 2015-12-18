
Int_t plot_field_xy(){

   clas12::mag::CLAS12MagneticField * mf = new clas12::mag::CLAS12MagneticField();

   Int_t  nXbins = 500;
   Int_t  nYbins = 500;

   double xmin = -400.0;
   double xmax =  400.0;
   double ymin = -400.0;
   double ymax =  400.0;

   TH2F * hBx = new TH2F("hBx","CLAS 12 magnetic field - Bx", nXbins,     xmin,xmax, nYbins,ymin,ymax);
   TH2F * hBy = new TH2F("hBy","CLAS 12 magnetic field - By", nXbins,     xmin,xmax, nYbins,ymin,ymax);
   TH2F * hBz = new TH2F("hBz","CLAS 12 magnetic field - Bz", nXbins,     xmin,xmax, nYbins,ymin,ymax);
   TH2F * hBperp = new TH2F("hBperp","CLAS 12 magnetic field - BT",nXbins,xmin,xmax, nYbins,ymin,ymax);


   for(int i=1;i<=nXbins; i++){
      for(int j=1;j<=nYbins; j++){

         Int_t bin = hBx->GetBin(i,j);

         double x = hBx->GetXaxis()->GetBinCenter(i);
         double y = hBx->GetYaxis()->GetBinCenter(j);
         double z = 300.0;

         TEveVector B = mf->GetFieldD(x,y,z);

         hBx->SetBinContent( bin, B.fX );
         hBy->SetBinContent( bin, B.fY );
         hBz->SetBinContent( bin, B.fZ );
         hBperp->SetBinContent( bin, TMath::Sqrt(B.fX*B.fX + B.fY*B.fY));


      }
   }

   TCanvas * c = new TCanvas();
   c->Divide(2,2);

   c->cd(1);
   hBx->Draw("colz");

   c->cd(2);
   hBy->Draw("colz");

   c->cd(3);
   hBz->Draw("colz");

   c->cd(4);
   hBperp->Draw("colz");

   return 0;
}
