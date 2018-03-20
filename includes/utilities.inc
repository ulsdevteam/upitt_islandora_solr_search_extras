<?php

/**
 * Set of functions used by this module - placed here so as to reduce clutter in the main .module file.
 */

/**
 * Helper function will inspect the object_url and _updateDefaultThumbnail
 */
function _updateDefaultThumbnail(&$solr_doc) {
  if (array_search('TN', $solr_doc['datastreams']) === FALSE) {
    if (!(array_search('info:fedora/islandora:findingAidCModel', $solr_doc['content_models']) === FALSE)) {
      $solr_doc['thumbnail_url'] = drupal_get_path('module', 'upitt_islandora_solr_search_extras') . '/images/findingaids4_lt_big_text.png';
    }
  }
}
