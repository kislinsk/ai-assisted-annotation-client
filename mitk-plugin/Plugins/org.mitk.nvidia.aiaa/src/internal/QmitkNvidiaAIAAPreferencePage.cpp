/*===================================================================

 The Medical Imaging Interaction Toolkit (MITK)

 Copyright (c) German Cancer Research Center,
 Division of Medical and Biological Informatics.
 All rights reserved.

 This software is distributed WITHOUT ANY WARRANTY; without
 even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.

 See LICENSE.txt or http://www.mitk.org for details.

 ===================================================================*/

#include "QmitkNvidiaAIAAPreferencePage.h"

#include <berryIPreferencesService.h>
#include <berryPlatform.h>

#include <ui_QmitkNvidiaAIAAPreferencePage.h>

const QString QmitkNvidiaAIAAPreferencePage::SERVER_URI = "server uri";
const QString QmitkNvidiaAIAAPreferencePage::NEIGHBORHOOD_SIZE = "neighborhood size";
const QString QmitkNvidiaAIAAPreferencePage::FLIP_POLY = "flip poly";

const QString QmitkNvidiaAIAAPreferencePage::DEFAULT_SERVER_URI = "http://0.0.0.0:5000/v1";
const int QmitkNvidiaAIAAPreferencePage::DEFAULT_NEIGHBORHOOD_SIZE = 1;
const bool QmitkNvidiaAIAAPreferencePage::DEFAULT_FLIP_POLY = false;

QmitkNvidiaAIAAPreferencePage::QmitkNvidiaAIAAPreferencePage()
    : m_Widget(nullptr),
      m_Ui(new Ui::QmitkNvidiaAIAAPreferencePage),
      m_Preferences(
          berry::Platform::GetPreferencesService()->GetSystemPreferences()->Node("/org.mitk.preferences.nvidia.aiaa")) {
}

QmitkNvidiaAIAAPreferencePage::~QmitkNvidiaAIAAPreferencePage() {
  delete m_Ui;
}

void QmitkNvidiaAIAAPreferencePage::Init(berry::IWorkbench::Pointer) {
}

bool QmitkNvidiaAIAAPreferencePage::PerformOk() {
  m_Preferences->Put(SERVER_URI, m_Ui->serverURILineEdit->text());
  m_Preferences->PutInt(NEIGHBORHOOD_SIZE, m_Ui->neighborhoodSizeSpinBox->value());
  m_Preferences->PutBool(FLIP_POLY, m_Ui->flipPolyCheckBox->isChecked());

  return true;
}

void QmitkNvidiaAIAAPreferencePage::PerformCancel() {
}

void QmitkNvidiaAIAAPreferencePage::Update() {
  m_Ui->serverURILineEdit->setText(m_Preferences->Get(SERVER_URI, DEFAULT_SERVER_URI));
  m_Ui->neighborhoodSizeSpinBox->setValue(m_Preferences->GetInt(NEIGHBORHOOD_SIZE, DEFAULT_NEIGHBORHOOD_SIZE));
  m_Ui->flipPolyCheckBox->setChecked(m_Preferences->GetBool(FLIP_POLY, DEFAULT_FLIP_POLY));
}

void QmitkNvidiaAIAAPreferencePage::CreateQtControl(QWidget* parent) {
  m_Widget = new QWidget(parent);
  m_Ui->setupUi(m_Widget);

  this->Update();
}

QWidget* QmitkNvidiaAIAAPreferencePage::GetQtControl() const {
  return m_Widget;
}
