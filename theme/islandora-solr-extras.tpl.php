<?php
/**
 * @file
 * Islandora solr search primary results template file.
 *
 * Variables available:
 * - $results: Primary profile results array
 *
 * @see template_preprocess_islandora_solr()
 */

?>
<?php if (empty($results)): ?>
  <p class="no-results"><?php print t('Sorry, but your search returned no results.'); ?></p>
<?php else: ?>
  <div class="islandora islandora-solr-search-results">
    <?php $row_result = 0; ?>
    <?php foreach($results as $key => $result): ?>
<?php // echo "<pre>". print_r($result, true)."</pre>";
 ?>
      <!-- Search result -->
      <div class="islandora-solr-search-result clear-block <?php print $row_result % 2 == 0 ? 'odd' : 'even'; ?>">
        <div class="islandora-solr-search-result-inner">
          <dl class="solr-thumb">
          <!-- Thumbnail -->
            <dt>
              <?php print $result['thumbnail']; ?>
            </dt>
            <dd></dd>
          </dl>
          <!-- Metadata -->
          <dl class="solr-fields islandora-inline-metadata">
            <?php if (count($result['page_solr_doc']) > 0) : ?>
            <dt>Book values:</dt>
            <?php endif; ?>
            <?php foreach($result['solr_doc'] as $key => $value): ?>
              <dd class="solr-value solr-field-parent <?php print $value['class']; ?>">
                <?php print $value['value']; ?>
              </dd>
            <?php endforeach; ?>
          </dl>
          <?php if (isset($result['page_thumbnail'])) : ?>
          <dl class="solr-page-thumb">
             <dt>
                 <?php print $result['page_thumbnail']; ?>
             </dt>
            <dd></dd>
          </dl>
          <?php endif; ?>
          <dl class="solr-fields islandora-inline-metadata">
          <?php if (count($result['page_solr_doc']) > 0) : ?>
            <dt class="solr-field-orig">Page values:</dt>
          <?php endif; ?>
            <?php foreach($result['page_solr_doc'] as $key => $value): ?>
              <dd class="solr-value solr-field-orig <?php print $value['class']; ?>">
                <?php print $value['value']; ?>
              </dd>
            <?php endforeach; ?>
          </dl>
        </div>
      </div>
    <?php $row_result++; ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>

